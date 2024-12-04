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
            print(lines[i][j])
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
