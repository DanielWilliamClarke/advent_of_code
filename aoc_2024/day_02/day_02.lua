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

local function assess_safety(check, within_range)
    return check and within_range
end

local function within_range(diff)
    return diff >= 1 and diff <= 3
end

local function diff(report, i)
    return math.abs(report[i] - report[i - 1])
end

local function sorted_asc(report, i)
    return report[i] < report[i - 1]
end

local function sorted_desc(report, i)
    return report[i] > report[i - 1]
end

local function assess_safety_asc(report, i)
    return assess_safety(sorted_asc(report, i), within_range(diff(report, i)))
end

local function assess_safety_desc(report, i)
    return assess_safety(sorted_desc(report, i), within_range(diff(report, i)))
end

local function safe_report (report)
    local safe_asc = true
    local safe_desc = true

    for i = 2, #report do
        safe_asc = safe_asc and assess_safety_asc(report, i)
        safe_desc = safe_desc and assess_safety_desc(report, i)
    end

    return safe_asc or safe_desc
end

local function count_safe_reports (reports)
    local total_safe = 0

    for _, report in ipairs(reports) do
        if safe_report(report) then
            total_safe = total_safe + 1
        end
    end

    return total_safe
end

local function part1()
    local reports = read_file.parse("input.txt", parse_reports)
    local total_safe = count_safe_reports(reports)

    print(total_safe)
    return total_safe
end

local function part2()
    local reports = read_file.parse("example.txt", parse_reports)

    local total_safe = count_safe_reports(reports)

    local recheck_reports = {}
    for _, report in ipairs(reports) do
        local new_report = { }

        for i = 2, #report do
            if (sorted_asc(report, i) or sorted_desc(report, i)) and within_range(diff(report, i)) then
                table.insert(new_report, report[i])
            end
        end

        if #new_report >= 4 and safe_report(new_report) then
           total_safe = total_safe + 1
        end
    end

    print(total_safe)
    return total_safe
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
        a.ok(timing.measure(part2) == 4, "Part 2 solution incorrect!")
    end
)
