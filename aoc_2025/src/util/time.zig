const std = @import("std");

pub fn startTimer() !std.time.Timer {
    return std.time.Timer.start();
}

pub fn readNs(t: *std.time.Timer) u64 {
    return t.read();
}
