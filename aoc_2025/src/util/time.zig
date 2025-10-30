const std = @import("std");

/// Measures a fallible thunk that returns void.
/// Usage:
/// const ns = try timeFn(fn() !void { try doWork(); });
pub fn timeFn(thunk: anytype) !u64 {
    var timer = try std.time.Timer.start();
    try thunk();
    return timer.read();
}

/// Measures an already executed step by bracketing with timer manually.
pub fn startTimer() !std.time.Timer {
    return std.time.Timer.start();
}

pub fn readNs(t: *std.time.Timer) u64 {
    return t.read();
}

/// Formats a duration in ns into a human-ish string (us/ms/s as appropriate).
pub fn fmtDuration(ns: u64) []const u8 {
    // Simple thresholds; no allocations – fixed strings.
    if (ns < 1_000) return "ns"; // Use with numeric value in print, e.g. {d} ns
    if (ns < 1_000_000) return "us";
    if (ns < 1_000_000_000) return "ms";
    return "s";
}
