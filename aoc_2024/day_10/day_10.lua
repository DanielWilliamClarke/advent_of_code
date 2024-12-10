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
    { -1, 0 },  -- up
    { 0,  -1 }, -- left
    { 1,  0 },  -- down
    { 0,  1 },  -- right
}

local function within_bounds(grid, position)
    return position[1] >= 1 and position[1] <= #grid and position[2] >= 1 and position[2] <= #grid[1]
end

local function is_new_nine(found_nines, position)
    for _, p in ipairs(found_nines) do
        if p[1] == position[1] and p[2] == position[2] then
            return false
        end
    end
    return true
end

local function index_grid(grid, p)
    return grid[p[1]][p[2]]
end

local function search(grid, found_nines, current_position, count_all)
    local altitude = index_grid(grid, current_position)
    if altitude == 9 and (count_all or is_new_nine(found_nines, current_position)) then
        table.insert(found_nines, current_position)
        return found_nines
    end

    for _, dir in ipairs(directions) do
        local next_position = {
            current_position[1] + dir[1],
            current_position[2] + dir[2],
        }

        if within_bounds(grid, next_position) then
            local next = index_grid(grid, next_position)

            if next ~= "." and next - altitude == 1 then
                found_nines = search(grid, found_nines, next_position, count_all)
            end
        end
    end

    return found_nines
end

local function part1()
    local grid = read_file.parse("input.txt", parse_line)
    local count = 0
    for y = 1, #grid do
        for x = 1, #grid[1] do
            if grid[y][x] == 0 then
                count = count + #search(grid, {}, { y, x })
            end
        end
    end
    return count
end

local function part2()
    local grid = read_file.parse("input.txt", parse_line)
    local count = 0
    for y = 1, #grid do
        for x = 1, #grid[1] do
            if grid[y][x] == 0 then
                count = count + #search(grid, {}, { y, x }, true)
            end
        end
    end
    return count
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
        a.ok(timing.measure(part2) == 1326, "Part 2 solution incorrect!")
    end
)
