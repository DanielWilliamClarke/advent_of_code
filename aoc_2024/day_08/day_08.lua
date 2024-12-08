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
                    grouped_nodes[frequency] = { }
                end

                table.insert(grouped_nodes[frequency], {
                    frequency=frequency,
                    coord={ y=y, x=x }
                })
            end
        end
    end
    return grouped_nodes
end

local function pair_up_nodes (nodes)
    local paired_nodes = {}

    for f,frequency in pairs(nodes) do
        if paired_nodes[f] == nil then
            paired_nodes[f] = { }
        end

        for _,left in ipairs(frequency) do
            for _,right in ipairs(frequency) do
                if left ~= right then
                    local pair = { left, right }

                    -- check if pair already present in pairs
                    local duplicate = false
                    for _,p in ipairs(paired_nodes[f]) do
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

local function print_nodes (nodes)
    for i,f in pairs(nodes) do
        print("FREQUENCY " .. i)
        for _,n in ipairs(f) do
            print("(" .. n.coord.x .. ", " .. n.coord.y .. ")")
        end
    end
end

local function print_pairs (nodes)
    for i,f in pairs(nodes) do
        print("FREQUENCY " .. i)
        for _,n in ipairs(f) do
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
    return { x=dx, y=dy }
end

local function is_new_antinode (antinodes, antinode)
    for _,n in ipairs(antinodes) do
        if n.x == antinode.x and n.y == antinode.y then
            return false
        end
    end

    return true
end

local function find_antinodes (grid, paired_nodes)
    local antinodes = {}
    for _,frequency in pairs(paired_nodes) do
        for _,p in ipairs(frequency) do
            local direction = get_direction(p[1].coord, p[2].coord)

            print("DIRECTION: x: " .. direction.x .. ", y: " .. direction.y)

            local first_antinode = {
                x=p[2].coord.x + direction.x,
                y=p[2].coord.y + direction.y
            }
            if within_bounds(grid, first_antinode) and is_new_antinode(antinodes, first_antinode) then
                print("Adding first antinode: x: " .. first_antinode.x .. ", y: " .. first_antinode.y)
                table.insert(antinodes, first_antinode)
            end

            local second_antinode = {
                x=p[1].coord.x + -direction.x,
                y=p[1].coord.y + -direction.y
            }
            if within_bounds(grid, second_antinode) and is_new_antinode(antinodes, second_antinode) then
                print("Adding second antinode: x: " .. second_antinode.x .. ", y: " .. second_antinode.y)
                table.insert(antinodes, second_antinode)
            end
        end
    end
    return antinodes
end

local function part1()
    local grid = read_file.parse("example.txt", parseLine)

    local nodes = extract_nodes(grid)
    print_nodes(nodes)

    local paired_nodes = pair_up_nodes(nodes)
    print_pairs(paired_nodes)

    local antinodes = find_antinodes(grid, paired_nodes)
    local count = #antinodes

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
        a.ok(timing.measure(part1) == 273, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
