const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day10.txt";
pub const example_path = "inputs/day10_example.txt";

const space = mecha.ascii.char(' ').discard();
const comma = mecha.ascii.char(',').discard();
const number = mecha.int(i64, .{});

fn charToState(ch: u8) bool {
    return switch (ch) {
        '.' => false,
        '#' => true,
        else => unreachable,
    };
}

const lightParser = mecha
    .oneOf(.{ mecha.ascii.char('.'), mecha.ascii.char('#') }) // match one space
    .map(charToState);

const lightsParser: mecha.Parser([]bool) = mecha.many(lightParser, .{});

const indicatorParser = mecha
    .combine(.{ mecha.ascii.char('[').discard(), lightsParser, mecha.ascii.char(']').discard() });

const numbersParser: mecha.Parser([]i64) = mecha.many(number, .{ .separator = comma });
const toggleParser = mecha
    .combine(.{ mecha.ascii.char('(').discard(), numbersParser, mecha.ascii.char(')').discard() });

const toggleSetParser: mecha.Parser([][]i64) = mecha.many(toggleParser, .{ .separator = space });

const joltParser: mecha.Parser([]i64) = mecha
    .combine(.{ mecha.ascii.char('{').discard(), numbersParser, mecha.ascii.char('}').discard() });

const Machine = struct {
    lights: []bool,
    toggles: [][]i64,
    jolts: []i64,

    pub fn deinit(self: *const Machine, alloc: std.mem.Allocator) void {
        alloc.free(self.lights);

        for (self.toggles) |t| alloc.free(t);
        alloc.free(self.toggles);

        alloc.free(self.jolts);
    }
};

const machineParser: mecha.Parser(Machine) = mecha.combine(.{
    indicatorParser,
    space,
    toggleSetParser,
    space,
    joltParser,
}).map(mecha.toStruct(Machine));

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]Machine {
    var machines: std.ArrayList(Machine) = .empty;
    defer machines.deinit(alloc);

    for (lines) |line| {
        const m: Machine = (try machineParser.parse(alloc, line)).value.ok;
        try machines.append(alloc, m);
    }

    return machines.toOwnedSlice(alloc);
}

fn backtrackToggleCombos(
    allocator: std.mem.Allocator,
    toggles: [][]const i64,
    start: usize,
    target_len: usize,
    path: *std.ArrayList([]const i64),
    result: *std.ArrayList([][]const i64),
) !void {
    if (path.items.len == target_len) {
        // Allocate exact-sized slice of toggle-slices
        const combo = try allocator.alloc([]const i64, target_len);
        std.mem.copy([]const i64, combo, path.items);
        try result.append(combo);
        return;
    }

    var i: usize = start;
    while (i < toggles.len) : (i += 1) {
        try path.append(toggles[i]);
        try backtrackToggleCombos(
            allocator,
            toggles,
            i + 1,
            target_len,
            path,
            result,
        );
        _ = path.pop();
    }
}

fn toggleCombinations(
    allocator: std.mem.Allocator,
    toggles: [][]const i64,
) ![][][]const i64 {
    var result = std.ArrayList([][]const i64).init(allocator);
    errdefer {
        for (result.items) |combo| allocator.free(combo);
        result.deinit();
    }

    if (toggles.len == 0) {
        return &[_][][]const i64{};
    }

    var path = std.ArrayList([]const i64).init(allocator);
    defer path.deinit();

    var k: usize = 1;
    while (k <= toggles.len) : (k += 1) {
        try backtrackToggleCombos(
            allocator,
            toggles,
            0,
            k,
            &path,
            &result,
        );
    }

    return result.toOwnedSlice();
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const machines = try parse(alloc, lines);
    defer {
        for (machines) |m| m.deinit(alloc);
        alloc.free(machines);
    }

    for (machines) |m| {
        std.debug.print("lights: {any}, toggles: {any}, jolts: {any} \n", .{ m.lights, m.toggles, m.jolts });
    }

    return 0;
}

pub fn part2(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

test "day10 part1 example" {
    try validate(part1).with(example_path).equals(7);
}

// test "day10 part1" {
//     try validate(part1).with(input_path).equals(0);
// }

// test "day10 part2 example" {
//     try validate(part2).with(example_path).equals(0);
// }

// test "day10 part2" {
//     try validate(part2).with(input_path).equals(0);
// }
