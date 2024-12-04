package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

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
        for match, instruction_a, instruction_b in string.gmatch(line, "(mul%((%d%d?%d?),(%d%d?%d?)%))") do
            result = result + (instruction_a * instruction_b)
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
    local should_do = true

    for _, line in ipairs(program) do
        local current_line = line
        local next_mul_pos = 0
        local next_do_pos = 0

        repeat
            if should_do then
                next_mul_pos = string.find(current_line, "(mul%((%d%d?%d?),(%d%d?%d?)%))") or math.huge
                if next_mul_pos == math.huge then
                    goto continue
                end

                local next_dont = string.find(current_line, "don't%(%)") or math.huge
                if next_dont < next_mul_pos then
                    should_do = false
                    goto continue
                end

                local match, instruction_a, instruction_b = string.match(current_line, "(mul%((%d%d?%d?),(%d%d?%d?)%))")

                result = result + (instruction_a * instruction_b)
                current_line = string.sub(current_line, next_mul_pos + #match)
            else
                next_do_pos = string.find(current_line, "do%(%)") or math.huge
                if next_do_pos ~= math.huge then
                    current_line = string.sub(current_line, next_do_pos)
                    should_do = true
                end
            end

            ::continue::
        until (next_mul_pos == math.huge or next_do_pos == math.huge)
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
