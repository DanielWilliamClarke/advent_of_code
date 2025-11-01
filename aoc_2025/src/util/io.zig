const std = @import("std");

// Read entire file into a string (caller owns memory)
pub fn readToString(alloc: std.mem.Allocator, path: []const u8) ![]const u8 {
    var file = try std.fs.cwd().openFile(path, .{});
    defer file.close();

    return file.readToEndAlloc(alloc, std.math.maxInt(usize));
}

/// Returns owned lines (each line duplicated) so you can free them independently.
/// Newlines ("\n") are not included. Works with both LF and CRLF.
pub fn readLinesOwned(alloc: std.mem.Allocator, path: []const u8) ![]const []const u8 {
    const content = try readToString(alloc, path);
    defer alloc.free(content);

    var list: std.ArrayList([]const u8) = .empty;
    errdefer {
        // free any duped lines we managed to push before an error
        for (list.items) |s| alloc.free(s);
        list.deinit(alloc);
    }

    var it = std.mem.splitScalar(u8, content, '\n');
    while (it.next()) |segment| {
        const line = std.mem.trimRight(u8, segment, "\r");
        const dup = try alloc.dupe(u8, line);

        // If append fails, free the dup immediately to avoid leaking it.
        list.append(alloc, dup) catch |e| {
            alloc.free(dup);
            return e;
        };
    }

    return list.toOwnedSlice(alloc);
}

/// Helper for callers to free the result of `readLinesOwned`.
pub fn freeLinesOwned(alloc: std.mem.Allocator, lines: []const []const u8) void {
    for (lines) |s| alloc.free(s);
    alloc.free(lines);
}
