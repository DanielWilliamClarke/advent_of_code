package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parseLine(line)
    local locationIds = {}
    for word in string.gmatch(line, "%S+") do
        table.insert(locationIds, word)
    end
    return {
        list1 = tonumber(locationIds[1]),
        list2 = tonumber(locationIds[2])
    }
end

local function part1()
    local lines = read_file.parse("input.txt", parseLine)

    -- Create lists and sort ASC
    local list1, list2 = {}, {}
    for _, line in ipairs(lines) do
        table.insert(list1, line.list1)
        table.insert(list2, line.list2)
    end
    table.sort(list1)
    table.sort(list2)

    -- Calculate distance
    local distance = 0
    for i = 1, #lines do
        distance = distance + math.abs(list1[i] - list2[i])
    end

    print("Part 1: " .. distance)
    return distance
end

local function part2()
    local lines = read_file.parse("input.txt", parseLine)

    local count_table = {}
    for _, line in ipairs(lines) do
        count_table[line.list2] = (count_table[line.list2] or 0) + 1
    end

    local similarity_score = 0
    for _, line in ipairs(lines) do
        local multiplier = (count_table[line.list1] or 0)
        similarity_score = similarity_score + (line.list1 * multiplier)
    end

    print("Part 2: " .. similarity_score)
    return similarity_score
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 2000468, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 18567089, "Part 2 solution incorrect!")
    end
)
