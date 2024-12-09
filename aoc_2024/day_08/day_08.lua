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

local function extract_nodes(grid)
    local grouped_nodes = {}
    for y = 1, #grid do
        for x = 1, #grid[1] do
            local frequency = grid[y][x]
            if frequency ~= "." then
                if grouped_nodes[frequency] == nil then
                    grouped_nodes[frequency] = {}
                end

                table.insert(
                    grouped_nodes[frequency],
                    {
                        frequency = frequency,
                        coord = {y = y, x = x}
                    }
                )
            end
        end
    end
    return grouped_nodes
end

local function pair_up_nodes(nodes)
    local paired_nodes = {}

    for f, frequency in pairs(nodes) do
        if paired_nodes[f] == nil then
            paired_nodes[f] = {}
        end

        for _, left in ipairs(frequency) do
            for _, right in ipairs(frequency) do
                if left ~= right then
                    local pair = {left, right}

                    -- check if pair already present in pairs
                    local duplicate = false
                    for _, p in ipairs(paired_nodes[f]) do
                        -- if left or right pair are present either l->r or r-> l reject it
                        if (p[1] == left and p[2] == right) or (p[1] == right and p[2] == left) then
                            duplicate = true
                            break
                        end
                    end

                    if not duplicate then
                        table.insert(paired_nodes[f], pair)
                    end
                end
            end
        end
    end
    return paired_nodes
end

local function print_nodes(nodes)
    for i, f in pairs(nodes) do
        print("FREQUENCY " .. i)
        for _, n in ipairs(f) do
            print("(" .. n.coord.x .. ", " .. n.coord.y .. ")")
        end
    end
end

local function print_pairs(nodes)
    for i, f in pairs(nodes) do
        print("FREQUENCY " .. i)
        for _, n in ipairs(f) do
            print("(" .. n[1].coord.x .. ", " .. n[1].coord.y .. "), (" .. n[2].coord.x .. ", " .. n[2].coord.y .. ")")
        end
    end
end

local function within_bounds(grid, coord)
    return coord.y >= 1 and coord.y <= #grid and coord.x >= 1 and coord.x <= #grid[1]
end

local function get_direction(a, b)
    local dx = b.x - a.x
    local dy = b.y - a.y
    return {x = dx, y = dy}
end

local function find_antinode(antinodes, antinode)
    for _, n in ipairs(antinodes) do
        if n.x == antinode.x and n.y == antinode.y then
            return antinode
        end
    end

    return nill
end

local function print_antinodes_on_grid(grid, antinodes)
     for y = 1, #grid do
        local row = {}
        for x = 1, #grid[1] do
            if (find_antinode(antinodes, {x=x, y=y}) == nil) then
                --table.insert(row, grid[y][x])
                table.insert(row, ".")
            else
               table.insert(row, "#")
            end
        end
        print(table.concat(row, ""))
    end
end

local function find_antinodes(grid, paired_nodes, repeat_nodes)
    local antinodes = {}
    for _, frequency in pairs(paired_nodes) do
        for _, p in ipairs(frequency) do
            local direction = get_direction(p[1].coord, p[2].coord)
            -- print("DIRECTION: x: " .. direction.x .. ", y: " .. direction.y)

            local first_antinode = p[2].coord
            if repeat_nodes and within_bounds(grid, first_antinode) and find_antinode(antinodes, first_antinode) == nil then
                -- print("Adding first antinode: x: " .. first_antinode.x .. ", y: " .. first_antinode.y)
                table.insert(antinodes, first_antinode)
            end
            repeat
                first_antinode = {
                    x = first_antinode.x + direction.x,
                    y = first_antinode.y + direction.y
                }
                -- print("Checking first antinode: x: " .. first_antinode.x .. ", y: " .. first_antinode.y)
                if within_bounds(grid, first_antinode) and find_antinode(antinodes, first_antinode) == nil then
                    -- print("Adding first antinode: x: " .. first_antinode.x .. ", y: " .. first_antinode.y)
                    table.insert(antinodes, first_antinode)
                end
            until not repeat_nodes or not within_bounds(grid, first_antinode)

            local second_antinode = p[1].coord
            if repeat_nodes and within_bounds(grid, second_antinode) and find_antinode(antinodes, second_antinode) == nil then
                -- print("Adding first antinode: x: " .. first_antinode.x .. ", y: " .. first_antinode.y)
                table.insert(antinodes, second_antinode)
            end
            repeat
                second_antinode = {
                    x = second_antinode.x + -direction.x,
                    y = second_antinode.y + -direction.y
                }
                 -- print("Checking second antinode: x: " .. second_antinode.x .. ", y: " .. second_antinode.y)
                if within_bounds(grid, second_antinode) and find_antinode(antinodes, second_antinode) == nil then
                    -- print("Adding second antinode: x: " .. second_antinode.x .. ", y: " .. second_antinode.y)
                    table.insert(antinodes, second_antinode)
                end
            until not repeat_nodes or not within_bounds(grid, second_antinode)
        end
    end
    return antinodes
end

local function part1()
    local grid = read_file.parse("input.txt", parseLine)

    local nodes = extract_nodes(grid)
    -- print_nodes(nodes)

    local paired_nodes = pair_up_nodes(nodes)
    -- print_pairs(paired_nodes)

    local antinodes = find_antinodes(grid, paired_nodes, false)
    -- print_antinodes_on_grid(grid, antinodes)

    local count = #antinodes
    print(count)
    return count
end

local function part2()
    local grid = read_file.parse("input.txt", parseLine)

    local nodes = extract_nodes(grid)
    -- print_nodes(nodes)

    local paired_nodes = pair_up_nodes(nodes)
    -- print_pairs(paired_nodes)

    local antinodes = find_antinodes(grid, paired_nodes, true)
    -- print_antinodes_on_grid(grid, antinodes)

    local count = #antinodes
    print(count)
    return count
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
