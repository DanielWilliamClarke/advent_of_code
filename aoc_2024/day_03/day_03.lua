package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local MUL_PATTERN = "(mul%((%d%d?%d?),(%d%d?%d?)%))";
local DONT_PATTERN = "don't%(%)"
local DO_PATTERN = "do%(%)"

local function part1()
    local program =
        read_file.parse(
        "input.txt",
        function(line)
            return line
        end
    )

    local result = 0
    for _, line in ipairs(program) do
        for _, a, b in string.gmatch(line, MUL_PATTERN) do
            result = result + (a * b)
        end
    end

    print(result)
    return result
end

local function part2()
    local program =
        read_file.parse(
        "input.txt",
        function(line)
            return line
        end
    )

    local result = 0
    local enabled = true
    for _, line in ipairs(program) do
        local next_pos = 0
        repeat
            if enabled then
                next_pos = string.find(line, MUL_PATTERN)
                if next_pos == nil then goto continue end

                local next_dont = string.find(line, DONT_PATTERN)
                if next_dont ~= nill and next_dont < next_pos then
                    enabled = false
                    goto continue
                end

                local match, a, b = string.match(line, MUL_PATTERN)
                result = result + (a * b)
                line = string.sub(line, next_pos + #match)
            else
                next_pos = string.find(line, DO_PATTERN)
                if next_pos == nil then goto continue end
                line = string.sub(line, next_pos)
                enabled = true
            end

            ::continue::
        until (next_pos == nil)
    end

    print(result)
    return result
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
        a.ok(timing.measure(part2) == 74361272, "Part 2 solution incorrect!")
    end
)
