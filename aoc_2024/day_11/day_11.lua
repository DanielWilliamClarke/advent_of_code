package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parse_line(line)
    local row = {}
    for number in string.gmatch(line, "%S+") do
        table.insert(row, tonumber(number))
    end
    return row
end

local function blink(stone, iterations_left, cache)
    if iterations_left == 0 then
        return 1
    end

    local key = table.concat({ stone, iterations_left }, "+")
    local index = iterations_left - 1
    if cache[key] == nil then
        if stone == 0 then
            cache[key] = blink(1, index, cache)
        elseif #tostring(stone) % 2 == 0 then
            local str = tostring(stone);
            local half_index = math.floor(#str / 2)
            local left = tonumber(string.sub(str, 1, half_index))
            local right = tonumber(string.sub(str, half_index + 1))
            cache[key] = blink(left, index, cache) + blink(right, index, cache)
        else
            cache[key] = blink(stone * 2024, index, cache)
        end
    end

    return cache[key]
end

local function part1()
    local stones = read_file.parse("input.txt", parse_line)[1]
    local count = 0
    for _,s in ipairs(stones) do
       count = count + blink(s, 25, {})
    end
    return count
end

local function part2()
    local stones = read_file.parse("input.txt", parse_line)[1]
    local count = 0
    for _,s in ipairs(stones) do
       count = count + blink(s, 75, {})
    end
    return count
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 203457, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 241394363462435, "Part 2 solution incorrect!")
    end
)
