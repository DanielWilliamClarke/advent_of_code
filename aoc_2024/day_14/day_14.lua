package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function part1()
    return 0
end

local function part2()
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
