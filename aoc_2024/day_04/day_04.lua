package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parseLine(line)
    local row = {}
    for char in string.gmatch(line, ".") do
        table.insert(row, char)
    end
    return row
end

local function part1()
    local lines = read_file.parse("input.txt", parseLine)

    local count = 0
    for y = 1, #lines do
        for x = 1, #lines[y] do
            if (lines[y][x] == "X") then
                for m_y = y - 1, y + 1 do
                    for m_x = x - 1, x + 1 do
                        local m_coord = {m_y, m_x}
                        if (
                            m_coord[1] >= 1 and m_coord[1] <= #lines and
                            m_coord[2] >= 1 and m_coord[2] <= #lines[y] and
                            lines[m_coord[1]][m_coord[2]] == "M"
                        ) then
                            local dir = {m_coord[1] - y, m_coord[2] - x}
                            local a_coord = {m_coord[1] + dir[1], m_coord[2] + dir[2]}

                            if (
                                a_coord[1] >= 1 and a_coord[1] <= #lines and
                                a_coord[2] >= 1 and a_coord[2] <= #lines[y] and
                                lines[a_coord[1]][a_coord[2]] == "A"
                            ) then
                                local s_coord = {m_coord[1] + (dir[1] * 2), m_coord[2] + (dir[2] * 2)}

                                if (
                                    s_coord[1] >= 1 and s_coord[1] <= #lines and
                                    s_coord[2] >= 1 and s_coord[2] <= #lines[y] and
                                    lines[s_coord[1]][s_coord[2]] == "S"
                                ) then
                                    count = count + 1
                                end
                            end
                        end
                    end
                end
            end
        end
    end

    print(count)
    return count
end

local function part2()
    print(0)
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 2578, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
