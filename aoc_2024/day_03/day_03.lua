package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function part1()
    local program = read_file.parse("input.txt", function (line) return line end)

    local result = 0
    for _,line in ipairs(program) do
        for match,instruction_a,instruction_b in string.gmatch(line, "(mul%((%d%d?%d?),(%d%d?%d?)%))") do
            -- print(match .. " - " .. instruction_a .. ", " .. instruction_b)
            result = result + (instruction_a * instruction_b)
        end
    end

    print(result)
    return result
end

local function part2()
    print(0)
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 175615763, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
