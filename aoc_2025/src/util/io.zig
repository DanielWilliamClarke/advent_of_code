const std = @import("std");

pub fn readToString(alloc: std.mem.Allocator, path: []const u8) ![]u8 {
    var file = try std.fs.cwd().openFile(path, .{ .read = true });
    defer file.close();

    return file.readToEndAlloc(alloc, std.math.maxInt(usize));
}

/// Returns owned lines (each line duplicated) so you can free them independently.
/// Newlines ("\n") are not included. Works with both LF and CRLF.
pub fn readLinesOwned(alloc: std.mem.Allocator, path: []const u8) ![][]u8 {
    const content = try readToString(alloc, path);
    errdefer alloc.free(content);

    var list = std.ArrayList([]u8).init(alloc);
    errdefer list.deinit();

    var it = std.mem.splitAny(u8, content, "\r\n");
    while (it.next()) |segment| {
        // Skip empty segments that are just from CR/LF boundaries if needed
        if (segment.len == 0) continue;
        const dup = try alloc.dupe(u8, segment);
        try list.append(dup);
    }

    // We can free the big content buffer now; each line is owned.
    alloc.free(content);

    return list.toOwnedSlice();
}
