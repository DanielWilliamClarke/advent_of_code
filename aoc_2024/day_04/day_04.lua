package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parseLine(line)
    local row = {}
    for char in string.gmatch(line, ".") do
        table.insert(row, char)
    end
    return row
end

local function bounds_check(lines, coord)
    return coord[1] >= 1 and coord[1] <= #lines and
       coord[2] >= 1 and coord[2] <= #lines[1]
end

local function top_left (coord)
    return {
        coord[1],
        coord[2]
    }
end

local function top_right (coord, length)
    return {
        coord[1],
        coord[2] + length
    }
end

local function bottom_left (coord, length)
    return {
        coord[1] + length,
        coord[2]
    }
end

local function bottom_right (coord, length)
    return {
        coord[1] + length,
        coord[2] + length
    }
end

local function part1()
    local lines = read_file.parse("input.txt", parseLine)

    local count = 0
    for y = 1, #lines do
        for x = 1, #lines[y] do
            if (lines[y][x] ~= "X") then
                goto next_x
            end

            for m_y = y - 1, y + 1 do
                for m_x = x - 1, x + 1 do
                    local next_coord = { m_y, m_x }
                    if (
                        not bounds_check(lines, next_coord) or
                        lines[next_coord[1]][next_coord[2]] ~= "M"
                    ) then
                        goto next_neighbor
                    end

                    local dir = { next_coord[1] - y, next_coord[2] - x }
                    next_coord = { next_coord[1] + dir[1], next_coord[2] + dir[2] }
                    if (
                        not bounds_check(lines, next_coord) or
                        lines[next_coord[1]][next_coord[2]] ~= "A"
                    ) then
                        goto next_neighbor
                    end

                    next_coord = { next_coord[1] + dir[1], next_coord[2] + dir[2] }
                    if (
                      not bounds_check(lines, next_coord) or
                      lines[next_coord[1]][next_coord[2]] ~= "S"
                    ) then
                        goto next_neighbor
                    end

                    count = count + 1
                    ::next_neighbor::
                end
            end

            ::next_x::
        end
    end

    print(count)
    return count
end

local function part2()
    local lines = read_file.parse("input.txt", parseLine)

    local count = 0
    for y = 1, #lines do
        for x = 1, #lines[y] do
              -- look in 3x3 windows, throughout grid
              -- bounds check windows, if can't fit then ignore it
             local size = 2;
             local limit = { y + size, x + size }
             if (not bounds_check(lines, limit)) then
                goto continue
             end

             -- check center between y and limit[2] and x and limit[1] for A
             if (lines[y + 1][x + 1] ~= 'A') then
                goto continue
             end

             -- if A is present check for present of 2 M in (tl, tr), (tr, br), (br, bl), (bl, tl) positions

             local s_coords = {}
             if (lines[y][x] == 'M' and lines[y][limit[2]] == "M") then
                -- top
                s_coords = {
                    { limit[1], x },
                    { limit[1], limit[2] }
                }
             elseif (lines[limit[1]][x] == 'M' and lines[limit[1]][limit[2]] == "M") then
                -- bottom
                 s_coords = {
                     { y, x },
                     { y, limit[2] }
                 }
             elseif (lines[y][x] == 'M' and lines[limit[1]][x] == "M") then
                -- left
                   s_coords = {
                       { y, limit[2] },
                       { limit[1], limit[2] }
                   }
             elseif (lines[y][limit[2]] == 'M' and lines[limit[1]][limit[2]] == "M") then
                -- right
                   s_coords = {
                       { y, x },
                       { limit[1], x }
                   }
             end

            if (
                s_coords[1] ~= nil and s_coords[2] ~= nil and
                bounds_check(lines, s_coords[1]) and
                lines[s_coords[1][1]][s_coords[1][2]] == 'S' and
                bounds_check(lines, s_coords[2]) and
                lines[s_coords[2][1]][s_coords[2][2]] == "S"
            ) then
                count = count + 1
            end



            ::continue::
        end
    end

    print(count)
    return count
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 2578, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 1972, "Part 2 solution incorrect!")
    end
)
