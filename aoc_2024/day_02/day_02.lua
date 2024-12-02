package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parse_reports(line)
    local report = {}

    for level in string.gmatch(line, "%S+") do
        table.insert(report, tonumber(level))
    end

    return report
end

local function assess_safety (safety, check, diff)
     return safety and check and diff >= 1 and diff <= 3
end

local function assess_safety_asc (safety, report, i)
    return assess_safety(safety, report[i - 1] < report[i], math.abs(report[i] - report[i - 1]))
end

local function assess_safety_desc (safety, report, i)
    return assess_safety(safety, report[i - 1] > report[i], math.abs(report[i - 1] - report[i]))
end

local function part1()
    local reports = read_file.parse("input.txt", parse_reports)

    local total_safe = 0
    for _, report in ipairs(reports) do
        local safe_asc = true
        local safe_desc = true

        for i = 2, #report do
            safe_asc = assess_safety_asc(safe_asc, report, i)
            safe_desc = assess_safety_desc(safe_desc, report, i)
        end

        if safe_asc or safe_desc then
          total_safe = total_safe + 1
        end
    end

    print(total_safe)
    return total_safe
end

local function part2()
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 287, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
