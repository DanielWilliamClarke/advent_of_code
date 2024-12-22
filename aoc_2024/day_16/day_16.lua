package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function print_paths(grid, paths)
    -- Create a copy of the grid to avoid modifying the original
    local visual_grid = {}
    for y = 1, #grid do
        visual_grid[y] = {}
        for x = 1, #grid[y] do
            visual_grid[y][x] = grid[y][x]
        end
    end

    -- Mark the paths on the visual grid
    for i, path in ipairs(paths) do
        for _, tile in ipairs(path) do
            local y, x = tile:match("^(%d+),(%d+)$")
            y, x = tonumber(y), tonumber(x)
            if visual_grid[y][x] ~= "S" and visual_grid[y][x] ~= "E" then
                visual_grid[y][x] = i
            end
        end
    end

    -- Print the visualized grid
    for y = 1, #visual_grid do
        for x = 1, #visual_grid[y] do
            io.write(visual_grid[y][x])
        end
        io.write("\n")
    end
end

local function parse_line(line)
    local row = {}
    for char in string.gmatch(line, ".") do
        table.insert(row, char)
    end
    return row
end

local directions = {
    {y = -1, x = 0, n = "N"}, -- North
    {y = 0, x = 1, n = "E"}, -- East
    {y = 1, x = 0, n = "S"}, -- South
    {y = 0, x = -1, n = "W"} -- West
}

local function find_position(grid, char)
    for y, row in ipairs(grid) do
        for x, cell in ipairs(row) do
            if cell == char then
                return {y = y, x = x}
            end
        end
    end
    return nil
end

local function is_valid_move(grid, pos)
    return pos.y > 0 and pos.x > 0 and pos.y <= #grid and pos.x <= #grid[1] and grid[pos.y][pos.x] ~= "#"
end

local function dijkstra(grid)
    local start = find_position(grid, "S")
    if not start then
        return nil
    end

    local goal = find_position(grid, "E")
    if not goal then
        return nil
    end

    -- Priority queue for cells
    local pq = {}
    local function push(queue, item)
        table.insert(queue, item)
        table.sort(
            queue,
            function(a, b)
                return a.cost < b.cost
            end
        )
    end
    local function pop(queue)
        return table.remove(queue, 1)
    end

    -- Distance map and visited set
    local distances = {}
    local visited = {}
    local previous = {}

    -- Initialize distances
    local start_key = start.y .. "," .. start.x
    distances[start_key] = 0
    push(pq, {pos = start, cost = 0, dir = "E"}) -- Start facing East (arbitrary)

    -- Record previous directions (for multiple paths)
    previous[start_key] = {}

    -- Dijkstra's algorithm
    while #pq > 0 do
        local current = pop(pq)
        local pos, cost, dir = current.pos, current.cost, current.dir
        local key = pos.y .. "," .. pos.x

        -- Skip if already visited
        if visited[key] then
            goto continue
        end
        visited[key] = true

        -- Explore neighbors
        for _, d in ipairs(directions) do
            local neighbor = {
                y = pos.y + d.y,
                x = pos.x + d.x
            }

            local neighbor_key = neighbor.y .. "," .. neighbor.x

            if is_valid_move(grid, neighbor) and not visited[neighbor_key] then
                -- Step cost = 1
                local new_cost = cost + 1

                -- If the direction changes, apply a turn cost
                local turn_cost = 0
                if dir ~= d.n then
                    turn_cost = 1000 -- Apply turn cost (e.g., 1000 for a 90-degree turn)
                end

                -- Calculate new cost with turn penalty if applicable
                new_cost = new_cost + turn_cost

                -- If it's a shorter path or unvisited
                if not distances[neighbor_key] or new_cost < distances[neighbor_key] then
                    distances[neighbor_key] = new_cost
                    previous[neighbor_key] = {key} -- Record the predecessor
                    push(pq, {pos = neighbor, cost = new_cost, dir = d.n})
                elseif new_cost == distances[neighbor_key] then
                    print("Adding" .. key .. "to previous at " .. neighbor_key)
                    -- Multiple paths: Add to the list of predecessors
                    table.insert(previous[neighbor_key], key)
                end
            end
        end

        ::continue::
    end

    -- Function to reconstruct all paths from start to goal
    local function reconstruct_paths(start_key, goal, previous)
        local goal_key = goal.y .. "," .. goal.x
        local paths = {}

        -- Backtrack function to generate all possible paths
        local function backtrack(key, path)
            table.insert(path, 1, key) -- Add current node to the path
            if key == start_key then
                table.insert(paths, {table.unpack(path)}) -- Add the completed path
                return
            end
            for _, prev in ipairs(previous[key] or {}) do
                backtrack(prev, {table.unpack(path)})
            end
        end

        backtrack(goal_key, {})
        return paths
    end

    -- Return the shortest cost and all possible paths from start to goal
    return distances[goal.y .. "," .. goal.x], function()
        return reconstruct_paths(start_key, goal, previous)
    end
end

local function part1()
    local grid = read_file.parse("input.txt", parse_line)
    local cost = dijkstra(grid)
    return cost
end

local function part2()
    local grid = read_file.parse("example.txt", parse_line)
    local _, get_paths = dijkstra(grid)

    if get_paths then
        local paths = get_paths()
        print(#paths)
        print_paths(grid, paths)

        local set = {}
        for _, path in ipairs(paths) do
          
            for _, tile in ipairs(path) do
                -- print(tile)
                set[tile] = tile
            end
        end

        -- Count the number of unique keys in the set
        local unique_count = 0
        for _ in pairs(set) do
            unique_count = unique_count + 1
        end

        print(unique_count)
        return unique_count
    end

    return 0
end

-- test(
--     "🎅 Part 1",
--     function(a)
--         a.ok(timing.measure(part1) == 85480, "Part 1 solution incorrect!")
--     end
-- )

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 45, "Part 2 solution incorrect!")
    end
)
