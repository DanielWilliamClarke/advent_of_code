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

local function part1()
    local lines = read_file.parse("example.txt", parseLine)

    for i = 1, #lines do
        for j = 1, #lines[i] do

            if (lines[i][j] == 'X') then

                for ni = i - 1, 3 do
                    for nj = j - 1, 3 do
                        if (
                            ni > 0 and ni <= #lines and
                            nj > 0 and nj <= #lines[j] and
                            lines[ni][nj] == 'M'
                        ) then
                            local dir = { i - ni, j - nj }

                            print(ni .. "," .. nj)
                            print(dir[1] .. "," .. dir[2])
                        end

                    end
               end

                -- search neighbours for an 'M'
                -- bounds check
                -- on finding an 'M' search for an 'A' and 'S' in its direction
                -- if found count XMAS
                -- keep searching until no more 'M's can be found in neighbours
                -- move on to the next X

            end

        end
    end

    print(0)
    return 0
end

local function part2()
   print(0)
       return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 0, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
