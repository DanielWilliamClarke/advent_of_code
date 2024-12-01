package.path = package.path .. ";../utils/?.lua"

local test = require 'simple_test'
local read_file = require 'read_file'

local function parseLine (line)
 local locationIds = {}
 for word in string.gmatch(line, "%S+") do  -- %S+ matches one or more non-space characters
   table.insert(locationIds, word)
 end
 return { list1 = tonumber(locationIds[1]), list2 = tonumber(locationIds[2]) }
end

local function part1 ()
    local lines = read_file.parse("input.txt", parseLine)

    -- Create lists and sort ASC
    local list1 = {}
    local list2 = {}
    for _, line in pairs(lines) do
        table.insert(list1, line.list1)
        table.insert(list2, line.list2)
    end
    table.sort(list1)
    table.sort(list2)

    -- Calculate distance
    local distance = 0
    for i,_ in pairs(lines) do
        distance = distance + math.abs(list1[i] - list2[i])
    end

    print("Part 1: " .. distance)
    return distance
end

test('Part 1', function(a)
  a.ok(part1() == 2000468, 'Part 1 solution incorrect!')
end)
