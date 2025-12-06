const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day05.txt";
pub const example_path = "inputs/day05_example.txt";

const Range = struct {
    start: i64,
    end: i64,
};

const Database = struct {
    ranges: []Range,
    ids: []i64,

    pub fn deinit(self: *const Database, alloc: std.mem.Allocator) void {
        alloc.free(self.ranges);
        alloc.free(self.ids);
    }
};

const dash = mecha.ascii.char('-').discard();
const number = mecha.int(i64, .{});

const rangeParser =
    mecha
        .combine(.{ number, dash, number })
        .map(mecha.toStruct(Range));

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) !Database {
    var ranges: std.ArrayList(Range) = .empty;
    defer ranges.deinit(alloc);

    var ids: std.ArrayList(i64) = .empty;
    defer ids.deinit(alloc);

    var parseRanges = true;
    for (lines) |line| {
        if (line.len == 0) {
            parseRanges = false;
        } else if (parseRanges) {
            const range: Range = (try rangeParser.parse(alloc, line)).value.ok;
            try ranges.append(alloc, range);
        } else {
            const id: i64 = (try number.parse(alloc, line)).value.ok;
            try ids.append(alloc, id);
        }
    }

    return Database{ .ranges = try ranges.toOwnedSlice(alloc), .ids = try ids.toOwnedSlice(alloc) };
}

fn countFresh(db: Database) i64 {
    var count: i64 = 0;

    for (db.ids) |id| {
        for (db.ranges) |range| {
            if (id >= range.start and id <= range.end) {
                count += 1;
                break; // is fresh - go to next id
            }
        }
    }

    return count;
}

fn countAllFreshIds(alloc: std.mem.Allocator, db: Database) !i64 {
    // Copy ranges so we can sort in place
    const ranges = try alloc.alloc(Range, db.ranges.len);
    std.mem.copyForwards(Range, ranges, db.ranges);
    defer alloc.free(ranges);

    // Sort by start, and then on end on tie break
    std.sort.block(Range, ranges, {}, struct {
        fn lessThan(_: void, a: Range, b: Range) bool {
            if (a.start == b.start) return a.end < b.end;
            return a.start < b.start;
        }
    }.lessThan);

    var normalised: std.ArrayList(Range) = .empty;
    defer normalised.deinit(alloc);

    // Now normalize ranges
    var current = ranges[0];
    var i: usize = 1;
    while (i < ranges.len) : (i += 1) {
        // If no overlap: push current, start a new one
        if (ranges[i].start > current.end) {
            try normalised.append(alloc, current);
            current = ranges[i];
        } else {
            // extend current.end to next.end, if range overlaps
            if (ranges[i].end > current.end) {
                current.end = ranges[i].end;
            }
        }
    }

    // push the last current range
    try normalised.append(alloc, current);

    // add up range sizes
    var count: i64 = 0;
    for (normalised.items) |range| {
        // std.debug.print("Start: {d}, End: {d}\n", .{ range.start, range.end });
        count += (range.end - range.start) + 1; // remember ranges are inclusive
    }

    return count;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const db = try parse(alloc, lines);
    defer db.deinit(alloc);

    return countFresh(db);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const db = try parse(alloc, lines);
    defer db.deinit(alloc);

    return try countAllFreshIds(alloc, db);
}

test "day05 part1 example" {
    try validate(part1).with(example_path).equals(3);
}

test "day05 part1" {
    try validate(part1).with(input_path).equals(635);
}

test "day05 part2 example" {
    try validate(part2).with(example_path).equals(14);
}

test "day05 part2" {
    try validate(part2).with(input_path).equals(369761800782619);
}
