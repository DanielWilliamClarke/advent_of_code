package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parseLine(line)
    local row = {}
    for char in string.gmatch(line, ".") do
        table.insert(
            row,
            {
                char = char,
                visited = false
            }
        )
    end
    return row
end

local function within_bounds(grid, coord)
    return coord[1] >= 1 and coord[1] <= #grid and coord[2] >= 1 and coord[2] <= #grid[1]
end

local function rotate_vector(coord, clockwise)
    -- coord is { y , x }
    if clockwise then
        return {coord[2], -coord[1]} -- x, -y
    else
        return {-coord[2], coord[1]} -- -x, y
    end
end

local function find_guard (grid)
    for y = 1, #grid do
        for x = 1, #grid[1] do
            if grid[y][x].char == "^" then
                return {y, x}
            end
        end
    end

    return {0, 0}
end

function copy_grid(grid)
    local copy = {}
    for i = 1, #grid do
        copy[i] = {}
        for j = 1, #grid[i] do
            copy[i][j] = grid[i][j]
        end
    end
    return copy
end


local function print_grid(grid)
    for y = 1, #grid do
        local row = {}

        for x = 1, #grid[1] do
            if grid[y][x].visited == true then
                table.insert(row, "X")
            else
                table.insert(row, grid[y][x].char)
            end
        end

        print(table.concat(row, ""))
    end
end

local function part1()
    local grid = read_file.parse("input.txt", parseLine)

    -- find guard
    local guard = find_guard(grid)

    local dir = {-1, 0}
    local exited = false

    -- Just in case the guard doesnt revisit its origin
    -- visit it to start with
    local visited_count = 1
    grid[guard[1]][guard[2]].visited = true

    repeat
        local np = {
            guard[1] + dir[1], -- y
            guard[2] + dir[2] -- x
        }

        if not within_bounds(grid, np) then
            exited = true
        else
            -- print(np[1]..","..np[2])
            local char = grid[np[1]][np[2]].char
            if char == "." or char == "^" then
                guard = np
                if not grid[np[1]][np[2]].visited then
                    visited_count = visited_count + 1
                    grid[np[1]][np[2]].visited = true
                end
            elseif char == "#" then
                dir = rotate_vector(dir, true)
            end
        end
    until (exited == true)

    -- print_grid(grid)

    print(visited_count)
    return visited_count
end

local function part2()
    local filename = "input.txt"
    local grid = read_file.parse(filename, parseLine)

    -- brute force, put an obstacle at each grid point and check for a cycle
    -- if cycle detected then count it
    -- how to detect a cycle??
    local cycles = 0

    for y = 1, #grid do
        for x = 1, #grid[1] do
            local previous_obstacles = {}

            -- copying is a bit jank so just regrab the file
            local new_grid = read_file.parse(filename, parseLine)

            local guard = find_guard(new_grid)
            local dir = {-1, 0}
            -- Just in case the guard doesnt revisit its origin
            -- visit it to start with
            new_grid[guard[1]][guard[2]].visited = true

            -- ignore guard origin point
            if y == guard[1] and x == guard[2] then
                goto continue
            end

            -- Add a new obstacle
            new_grid[y][x].char = "#"

            -- find the loop - somehow
            while true do
                local np = {
                    guard[1] + dir[1], -- y
                    guard[2] + dir[2] -- x
                }

                if not within_bounds(new_grid, np) then
                    goto continue
                else
                    local char = new_grid[np[1]][np[2]].char
                    if char == "." or char == "^" then
                        guard = np
                        if not new_grid[np[1]][np[2]].visited then
                            new_grid[np[1]][np[2]].visited = true
                        end
                    elseif char == "#" then
                         for i = #previous_obstacles, 1, -1 do
                            local obstacle = previous_obstacles[i]
                            if (
                                obstacle.coord[1] == np[1] and obstacle.coord[2] == np[2] and
                                obstacle.dir[1] == dir[1] and obstacle.dir[2] == dir[2]
                            ) then
                                cycles = cycles + 1
                                -- print_grid(new_grid)
                                goto continue
                            end
                        end

                        table.insert(previous_obstacles, {
                            dir=dir,
                            coord=np
                        })
                        dir = rotate_vector(dir, true)
                    end
                end
            end

            ::continue::
        end
    end

    print(cycles)
    return cycles
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 4988, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 1697, "Part 2 solution incorrect!")
    end
)
