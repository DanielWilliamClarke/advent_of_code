const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day08.txt";
pub const example_path = "inputs/day08_example.txt";

var ITERATIONS: usize = 1000;

const JunctionBox = struct {
    x: i64,
    y: i64,
    z: i64,

    pub fn eql(self: *const JunctionBox, other: *const JunctionBox) bool {
        return self.*.x == other.x and self.*.y == other.y and self.*.z == other.z;
    }
};

const comma = mecha.ascii.char(',').discard();
const number = mecha.int(i64, .{});

const boxParser: mecha.Parser(JunctionBox) = mecha
    .manyN(number, 3, .{ .separator = comma })
    .map(mecha.toStruct(JunctionBox));

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]JunctionBox {
    var boxes: std.ArrayList(JunctionBox) = .empty;
    defer boxes.deinit(alloc);

    for (lines) |line| {
        const box: JunctionBox = (try boxParser.parse(alloc, line)).value.ok;
        try boxes.append(alloc, box);
    }

    return boxes.toOwnedSlice(alloc);
}

fn squaredDistance(a: *const JunctionBox, b: *const JunctionBox) i64 {
    const dx: i64 = a.x - b.x;
    const dy: i64 = a.y - b.y;
    const dz: i64 = a.z - b.z;

    return dx * dx + dy * dy + dz * dz;
}

const Cable = struct {
    a: JunctionBox,
    b: JunctionBox,
    d2: i64, // squared distance
};

fn connectBoxes(alloc: std.mem.Allocator, boxes: []JunctionBox, iterations: usize, isPart2: bool) ![]std.AutoHashMap(JunctionBox, bool) {
    var circuts: std.ArrayList(Cable) = .empty;
    defer circuts.deinit(alloc);

    // Build pairwise edges with squared distance
    for (0..(boxes.len - 1)) |i| {
        for ((i + 1)..boxes.len) |j| {
            const a = boxes[i];
            const b = boxes[j];

            const d = squaredDistance(&a, &b); // i64

            try circuts.append(alloc, .{ .a = a, .b = b, .d2 = d });
        }
    }

    // Sort edges by distance ascending
    std.sort.block(
        Cable,
        circuts.items,
        {},
        struct {
            fn lessThan(_: void, a: Cable, b: Cable) bool {
                return a.d2 < b.d2;
            }
        }.lessThan,
    );

    // Each entry is a cluster/set of JunctionBox
    var circutSet: std.ArrayList(std.AutoHashMap(JunctionBox, bool)) = .empty;
    defer {
        for (circutSet.items) |*cs| cs.deinit();
        circutSet.deinit(alloc);
    }

    // Process first `iterations` edges
    for (circuts.items, 0..) |c, i| {
        if (!isPart2 and i >= iterations) {
            // std.debug.print("Max iterations hit {d} \n", .{i});
            break;
        }

        // subset holds indices into circutSet (NOT pointers)
        var subset: std.ArrayList(usize) = .empty;
        defer subset.deinit(alloc);

        // collect indices of clusters that contain a or b
        for (circutSet.items, 0..) |*s, idx| {
            if (s.contains(c.a) or s.contains(c.b)) {
                try subset.append(alloc, idx);
            }
        }

        if (subset.items.len > 0) {
            // base cluster index and pointer
            const base_idx = subset.items[0];
            const base = &circutSet.items[base_idx];

            // ensure both endpoints in the base cluster
            try base.put(c.a, true);
            try base.put(c.b, true);

            // merge all other matching clusters into base and then remove them
            if (subset.items.len > 1) {
                const others = subset.items[1..];

                // first merge contents
                for (others) |idx| {
                    const other = &circutSet.items[idx];
                    var it = other.iterator();
                    while (it.next()) |entry| {
                        try base.put(entry.key_ptr.*, entry.value_ptr.*);
                    }
                }

                // sort indices descending so swapRemove doesn't corrupt remaining indices
                std.sort.block(
                    usize,
                    others,
                    {},
                    struct {
                        fn greater(_: void, a: usize, b: usize) bool {
                            return a > b;
                        }
                    }.greater,
                );

                // remove the merged clusters
                for (others) |idx| {
                    var removed = circutSet.swapRemove(idx);
                    removed.deinit();
                }
            }

            if (isPart2 and base.count() == boxes.len) {
                var result = try alloc.alloc(std.AutoHashMap(JunctionBox, bool), 1);

                result[0] = std.AutoHashMap(JunctionBox, bool).init(alloc);
                try result[0].put(c.a, true);
                try result[0].put(c.b, true);

                return result;
            }
        } else {
            // no existing cluster → create new cluster for this edge
            var newSet = std.AutoHashMap(JunctionBox, bool).init(alloc);
            try newSet.put(c.a, true);
            try newSet.put(c.b, true);
            try circutSet.append(alloc, newSet);
        }
    }

    // Sort clusters by descending size
    std.sort.block(
        std.AutoHashMap(JunctionBox, bool),
        circutSet.items,
        {},
        struct {
            fn greaterThan(_: void, a: std.AutoHashMap(JunctionBox, bool), b: std.AutoHashMap(JunctionBox, bool)) bool {
                return a.count() > b.count();
            }
        }.greaterThan,
    );

    return circutSet.toOwnedSlice(alloc);
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const boxes = try parse(alloc, lines);
    defer alloc.free(boxes);

    const circuts = try connectBoxes(alloc, boxes, ITERATIONS, false);
    defer {
        for (circuts) |*cs| cs.deinit();
        alloc.free(circuts);
    }

    // Multiply sizes of the top 3 clusters (guard if fewer than 3 exist)
    const max_clusters = @min(circuts.len, 3);
    var total: i64 = 1;
    for (circuts[0..max_clusters]) |c| {
        total *= @as(i64, @intCast(c.count()));
    }

    return total;
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const boxes = try parse(alloc, lines);
    defer alloc.free(boxes);

    const circuts = try connectBoxes(alloc, boxes, 0, true);
    defer {
        for (circuts) |*cs| cs.deinit();
        alloc.free(circuts);
    }

    // multiple the x coords
    var total: i64 = 1;
    var iter = circuts[0].iterator();
    while (iter.next()) |entry| {
        total *= entry.key_ptr.*.x;
    }

    return total;
}

test "day08 part1 example" {
    ITERATIONS = 10;
    try validate(part1).with(example_path).equals(40);
}

test "day08 part1" {
    ITERATIONS = 1000;
    try validate(part1).with(input_path).equals(122636);
}

test "day08 part2 example" {
    try validate(part2).with(example_path).equals(25272);
}

test "day08 part2" {
    try validate(part2).with(input_path).equals(9271575747);
}
