const std = @import("std");

// File I/O utilities for reading puzzle inputs

// Read entire file into a string (caller owns memory)
pub fn readToString(alloc: std.mem.Allocator, path: []const u8) ![]u8 {
    var file = try std.fs.cwd().openFile(path, .{});
    defer file.close();

    return file.readToEndAlloc(alloc, std.math.maxInt(usize));
}

/// Returns owned lines (each line duplicated) so you can free them independently.
/// Newlines ("\n") are not included. Works with both LF and CRLF.
pub fn readLinesOwned(alloc: std.mem.Allocator, path: []const u8) ![]const []const u8 {
    const content = try readToString(alloc, path);
    errdefer alloc.free(content);

    var list: std.ArrayList([]const u8) = .empty;
    errdefer list.deinit(alloc);

    var it = std.mem.splitScalar(u8, content, '\n');
    while (it.next()) |segment| {
        const line = std.mem.trimRight(u8, segment, "\r");
        const dup = try alloc.dupe(u8, line);
        try list.append(alloc, dup);
    }

    // We can free the big content buffer now; each line is owned.
    alloc.free(content);

    return list.toOwnedSlice(alloc);
}
