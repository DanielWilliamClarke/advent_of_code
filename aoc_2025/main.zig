const std = @import("std");
const expect = std.testing.expect;

pub fn main() void {
    std.debug.print("Hello, {s}!\n", .{"World"});
}

test "always succeeds" {
    try expect(true);
}
