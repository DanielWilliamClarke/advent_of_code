const std = @import("std");

// Timing utilities for benchmarking puzzle solutions

/// Measures an already executed step by bracketing with timer manually.
pub fn startTimer() !std.time.Timer {
    return std.time.Timer.start();
}

pub fn readNs(t: *std.time.Timer) u64 {
    return t.read();
}
