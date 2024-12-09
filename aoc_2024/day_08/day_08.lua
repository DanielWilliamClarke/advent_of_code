package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function print_nodes(nodes)
    for i, f in pairs(nodes) do
        print("FREQUENCY " .. i)
        for _, n in ipairs(f) do
            print("(" .. n.x .. ", " .. n.y .. ")")
        end
    end
end

local function print_pairs(nodes)
    for i, f in pairs(nodes) do
        print("FREQUENCY " .. i)
        for _, n in ipairs(f) do
            print("(" .. n[1].x .. ", " .. n[1].y .. "), (" .. n[2].x .. ", " .. n[2].y .. ")")
        end
    end
end

local function print_antinodes_on_grid(grid, antinodes)
    for y = 1, #grid do
        local row = {}
        for x = 1, #grid[1] do
            if (find_antinode(antinodes, {x = x, y = y}) == nil) then
                -- table.insert(row, ".")
                table.insert(row, grid[y][x])
            else
                table.insert(row, "#")
            end
        end
        print(table.concat(row, ""))
    end
end

local function parseLine(line)
    local row = {}
    for char in string.gmatch(line, ".") do
        table.insert(row, char)
    end
    return row
end

local function extract_nodes(grid)
    local grouped_nodes = {}
    for y = 1, #grid do
        for x = 1, #grid[1] do
            local frequency = grid[y][x]
            if frequency ~= "." then
                if grouped_nodes[frequency] == nil then
                    grouped_nodes[frequency] = {}
                end

                table.insert(grouped_nodes[frequency], {y = y, x = x})
            end
        end
    end
    return grouped_nodes
end

local function is_known_pair(paired_nodes, left, right)
    for _, p in ipairs(paired_nodes) do
        if ((p[1] == left and p[2] == right) or (p[1] == right and p[2] == left)) then
            return true
        end
    end
    return false
end

local function pair_up_nodes(nodes)
    local paired_nodes = {}
    for f, frequency in pairs(nodes) do
        if paired_nodes[f] == nil then
            paired_nodes[f] = {}
        end

        for _, left in ipairs(frequency) do
            for _, right in ipairs(frequency) do
                if left ~= right and not is_known_pair(paired_nodes[f], left, right) then
                    table.insert(paired_nodes[f], {left, right})
                end
            end
        end
    end
    return paired_nodes
end

local function find_antinode(antinodes, antinode)
    for _, n in ipairs(antinodes) do
        if n.x == antinode.x and n.y == antinode.y then
            return antinode
        end
    end
    return nil
end

local function within_bounds(grid, coord)
    return coord.y >= 1 and coord.y <= #grid and coord.x >= 1 and coord.x <= #grid[1]
end

local function manhattan_distance(a, b)
    return {x = b.x - a.x, y = b.y - a.y}
end

local function find_antinodes_for_origin(grid, antinodes, origin, direction, repeat_nodes)
    if repeat_nodes and find_antinode(antinodes, origin) == nil then
        table.insert(antinodes, origin)
    end
    repeat
        origin = {
            x = origin.x + direction.x,
            y = origin.y + direction.y
        }
        if within_bounds(grid, origin) and find_antinode(antinodes, origin) == nil then
            table.insert(antinodes, origin)
        end
    until not repeat_nodes or not within_bounds(grid, origin)
end

local function find_antinodes(grid, paired_nodes, repeat_nodes)
    local antinodes = {}
    for _, frequency in pairs(paired_nodes) do
        for _, p in ipairs(frequency) do
            local direction = manhattan_distance(p[1], p[2])
            find_antinodes_for_origin(grid, antinodes, p[2], direction, repeat_nodes)
            local r_direction = manhattan_distance(p[2], p[1])
            find_antinodes_for_origin(grid, antinodes, p[1], r_direction, repeat_nodes)
        end
    end
    return antinodes
end

local function part1()
    local grid = read_file.parse("input.txt", parseLine)
    return #find_antinodes(grid, pair_up_nodes(extract_nodes(grid)), false)
end

local function part2()
    local grid = read_file.parse("input.txt", parseLine)
    return #find_antinodes(grid, pair_up_nodes(extract_nodes(grid)), true)
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 273, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 1017, "Part 2 solution incorrect!")
    end
)
