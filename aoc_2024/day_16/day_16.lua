package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

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
    local start_key = start.y .. "," .. start.x .. ",E" -- Facing East to start
    distances[start_key] = 0
    push(pq, {pos = start, cost = 0, dir = "E"})

    while #pq > 0 do
        local current = pop(pq)
        local pos, cost, dir = current.pos, current.cost, current.dir

        -- Mark as visited
        local key = pos.y .. "," .. pos.x .. dir
        if visited[key] then
            goto continue
        end
        visited[key] = true

        -- Check if we've reached the goal
        if pos.y == goal.y and pos.x == goal.x then
            -- Reconstruct path
            local path = {}
            local trace = key
            while trace do
                table.insert(path, 1, trace)
                trace = previous[trace]
            end
            return path, cost
        end

        -- Explore neighbors
        for _, d in ipairs(directions) do
            local neighbor = {
                y = pos.y + d.y,
                x = pos.x + d.x
            }

            local neighbor_key = neighbor.y .. "," .. neighbor.x .. d.n

            if is_valid_move(grid, neighbor) and not visited[neighbor_key] then
                local turn_cost = (d.n ~= dir) and 1000 or 0 -- 1000 cost for turning
                local new_cost = cost + 1 + turn_cost -- Step cost = 1, Turn cost = 1000

                if not distances[neighbor_key] or new_cost < distances[neighbor_key] then
                    distances[neighbor_key] = new_cost
                    previous[neighbor_key] = key
                    push(
                        pq,
                        {
                            pos = neighbor,
                            cost = new_cost,
                            dir = d.n
                        }
                    )
                end
            end
        end

        ::continue::
    end

    return nil -- No path found
end

local function part1()
    local grid = read_file.parse("input.txt", parse_line)
    local _, cost = dijkstra(grid)
    return cost
end

local function part2()
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 85480, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
