const std = @import("std");

// Fill a buffer with random single-byte symbols from `fills`
fn fillLine(
    rand: std.Random,
    fills: []const []const u8,
    width: usize,
    buf: []u8,
) []const u8 {
    for (buf[0..width]) |*b| {
        const sym = fills[rand.uintLessThan(usize, fills.len)];
        b.* = sym[0];
    }
    return buf[0..width];
}

pub fn printTree(day: u8) void {
    var rng = std.Random.DefaultPrng.init(@as(u64, day));

    const rand = rng.random();

    const fills: []const []const u8 = &.{ "+", "o", "*", "~", "=", "#" };
    const stars: []const []const u8 = &.{
        "⭐️",
        "🌟",
        "💫",
        "🎁",
        "🎅",
        "🦌",
        "🥙",
        "✨",
    };
    const ground_opts: []const []const u8 = &.{
        "          [🎁]    [🎁]",
        "         ~~~~~~~~~~~~~~~",
        "       [__]  [🎁🎁]  [__]",
        "",
    };

    var buf2: [2]u8 = undefined;
    var buf4: [4]u8 = undefined;
    var buf6: [6]u8 = undefined;
    var buf8: [8]u8 = undefined;
    var buf10: [10]u8 = undefined;

    const t2 = fillLine(rand, fills, 2, &buf2);
    const t4 = fillLine(rand, fills, 4, &buf4);
    const t6 = fillLine(rand, fills, 6, &buf6);
    const t8 = fillLine(rand, fills, 8, &buf8);
    const t10 = fillLine(rand, fills, 10, &buf10);

    const ground = ground_opts[rand.uintLessThan(usize, ground_opts.len)];
    const star = stars[day % stars.len];

    std.debug.print(
        \\                |
        \\              - {s} -
        \\               /\\
        \\              /{s}\\
        \\             /{s}\\
        \\            /{s}\\
        \\           /{s}\\
        \\          /{s}\\
        \\              _||_
        \\{s}
        \\== Advent Of Code 2025 - Day {d} ==
        \\
    ,
        .{ star, t2, t4, t6, t8, t10, ground, day },
    );
}
