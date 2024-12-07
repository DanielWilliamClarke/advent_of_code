package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parseLine(line)
    local target = 0;
    local operands = {}

    for left, right in string.gmatch(line, "(%d+):%s*([%d%s]+)") do
        target = tonumber(left)

        for num in string.gmatch(right, "%d+") do
            table.insert(operands, tonumber(num))
        end
    end

    return {
        target=target,
        operands=operands
    }
end

local function solve(target, operands, current, index, part2)
    -- print("INDEX:" .. index .. " CURRENT:" .. current)

    -- Handle case where we've reached the end of operands
    if index > #operands then
        local solved = target == current
        -- print("END REACHED: CURRENT=" .. current .. " SOLVED=" .. tostring(solved))
        return solved
    end

    -- Get next operand
    local next = operands[index]
    local next_index = index + 1
    -- print("NEXT OPERAND: " .. next)

    -- Try addition
    local sum = current + next
    -- print("CURRENT=" .. current .. " ADDING=" .. next .. " RESULT=" .. sum)
    if solve(target, operands, sum, next_index, part2) then
        -- print("ADDING + SOLVED: RESULT=" .. sum)
        return true
    end

    -- Try multiplication (only if it doesn't exceed the target)
    local mult = current * next
    if mult <= target then
        -- print("CURRENT=" .. current .. " MULTIPLYING=" .. next .. " RESULT=" .. mult)
        if solve(target, operands, mult, next_index, part2) then
            -- print("MULTIPLY * SOLVED: RESULT=" .. mult)
            return true
        end
    else
       --  print("PRUNING: MULTIPLY RESULT=" .. mult .. " > TARGET=" .. target)
    end

    if part2 then
        -- Try concatenation of current and next
        local concat = tonumber(tostring(current)..tostring(next))
        -- print("CURRENT=" .. current .. " CONCAT=" .. next .. " RESULT=" .. concat)
        if solve(target, operands, concat, next_index, part2) then
           -- print("CONCAT + SOLVED: RESULT=" .. concat)
           return true
        end
    end

    -- print("FAILED: CURRENT=" .. current)
    return false -- Backtrack
end

local function part1()
    local equations = read_file.parse("input.txt", parseLine)

    local total = 0
    for _,e in ipairs(equations) do
        if solve(e.target, e.operands, e.operands[1], 2, false) then
            total = total + e.target
        end
    end

    print(total)
    return total
end

local function part2()
     local equations = read_file.parse("input.txt", parseLine)

    local total = 0
    for _,e in ipairs(equations) do
        if solve(e.target, e.operands, e.operands[1], 2, true) then
            total = total + e.target
        end
    end

    print(total)
    return total
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 12839601725877, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 149956401519484, "Part 2 solution incorrect!")
    end
)
