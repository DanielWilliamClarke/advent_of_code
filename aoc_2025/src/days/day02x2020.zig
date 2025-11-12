const std = @import("std");
const mecha = @import("mecha");

const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day02x2020.txt";
pub const example_path = "inputs/day02x2020_example.txt";

//1-3 a: abcde
const PasswordPolicy = struct {
    min: i32,
    max: i32,
    letter: u8,
    password: []const u8,
};

const number = mecha.int(i32, .{ .max_digits = 2 });
const dash = mecha.ascii.char('-').discard();
const whitespace = mecha.ascii.whitespace.discard();
const letter = mecha.ascii.range('a', 'z');
const colon = mecha.ascii.char(':').discard();

const password =
    mecha
        .combine(.{ number, dash, number, whitespace, letter, colon, whitespace, mecha.rest.asStr() })
        .map(mecha.toStruct(PasswordPolicy));

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]PasswordPolicy {
    var passwords: std.ArrayList(PasswordPolicy) = .empty;
    defer passwords.deinit(alloc);

    for (lines) |line| {
        const parsed = (try password.parse(alloc, line)).value.ok;
        try passwords.append(alloc, parsed);
    }

    return passwords.toOwnedSlice(alloc);
}

fn countInvalidViaMinMaxCount(passwords: []PasswordPolicy) i64 {
    var count: i64 = 0;

    for (passwords) |p| {
        var iter = std.mem.splitScalar(u8, p.password, p.letter);

        var parts_count: i64 = -1; // pre-offset
        while (iter.next()) |_| {
            parts_count += 1;
        }

        if (parts_count >= p.min and parts_count <= p.max) {
            count += 1;
        }
    }

    return count;
}

fn countInvalidViaIndexing(passwords: []PasswordPolicy) i64 {
    var count: i64 = 0;

    for (passwords) |p| {
        const first = p.password[@intCast(p.min - 1)] == p.letter;
        const second = p.password[@intCast(p.max - 1)] == p.letter;

        if (first ^ second) {
            count += 1;
        }
    }

    return count;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const passwords = try parse(alloc, lines);
    defer alloc.free(passwords);

    return countInvalidViaMinMaxCount(passwords);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const passwords = try parse(alloc, lines);
    defer alloc.free(passwords);

    return countInvalidViaIndexing(passwords);
}

test "day02 2020 example" {
    try validate(part1).with(example_path).equals(2);
}

test "day01 part1" {
    try validate(part1).with(input_path).equals(467);
}

test "day01 part2" {
    try validate(part2).with(input_path).equals(441);
}
