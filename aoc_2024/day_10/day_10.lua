package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function print_grid(grid)
    for y = 1, #grid do
        local row = {}
        for x = 1, #grid[1] do
            table.insert(row, grid[y][x])
        end
        print(table.concat(row, ""))
    end
end

local function parse_line(line)
    local row = {}
    for char in string.gmatch(line, ".") do
        if char == "." then
            table.insert(row, char)
        else
            table.insert(row, tonumber(char))
        end
    end
    return row
end

local directions = {
    { -1, 0 }, -- up
    { 0,  -1 }, -- left
    { 1,  0 }, -- down
    { 0,  1 }, -- right
}

local function within_bounds(grid, coord)
    return coord[1] >= 1 and coord[1] <= #grid and coord[2] >= 1 and coord[2] <= #grid[1]
end

local function new_nine(nines, pos)
    for _, coord in ipairs(nines) do
        if coord[1] == pos[1] and coord[2] == pos[2] then
            return false
        end
    end
    return true
end

local function search(grid, pos, nines)
    local altitude = grid[pos[1]][pos[2]]
    if altitude == 9 and new_nine(nines, pos) then
        table.insert(nines, pos)
        return nines
    end

    for _, dir in ipairs(directions) do
        local np = {
            pos[1] + dir[1],
            pos[2] + dir[2],
        }

        if within_bounds(grid, np) then
            local next = grid[np[1]][np[2]]

            if next ~= "." and next - altitude == 1 then
                search(grid, np, nines)
            end
        end
    end

    return nines
end

local function part1()
    local grid = read_file.parse("input.txt", parse_line)
    local count = 0
    for y = 1, #grid do
        for x = 1, #grid[1] do
            if grid[y][x] == 0 then
                count = count + #search(grid, { y, x }, {})
            end
        end
    end

    return count
end

local function part2()
    print(0)
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 709, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
