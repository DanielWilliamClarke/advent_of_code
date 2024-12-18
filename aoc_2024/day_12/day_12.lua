package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function print_grid(grid, current)
    for y = 1, #grid do
        local row = {}
        for x = 1, #grid[1] do
            if current ~= nil and current[1] == y and current[2] == x then
                table.insert(row, "#")
            else 
                table.insert(row, grid[y][x].garden)
            end
        end
        print(table.concat(row, ""))
    end
    print("-------------------")
end

local function parse_line(line)
    local row = {}
    for char in string.gmatch(line, ".") do
        table.insert(row, {
            garden=char,
            visited=false
        })
    end
    return row
end

local directions = {
    { -1, 0 },  -- up
    { 0,  -1 }, -- left
    { 1,  0 },  -- down
    { 0,  1 },  -- right
}

local function within_bounds(grid, position)
    return position[1] >= 1 and position[1] <= #grid and position[2] >= 1 and position[2] <= #grid[1]
end

local function index_grid(grid, p)
    return grid[p[1]][p[2]]
end

local function manhattan_distance(a, b)
    return math.abs(b[1] - a[1]) + math.abs(b[2] - a[2])
end

local function search(grid, current, garden, region)
    local current_garden = index_grid(grid, current)
    current_garden.visited = true

    for _, dir in ipairs(directions) do
        local next_position = {
            current[1] + dir[1],
            current[2] + dir[2],
        }

        if within_bounds(grid, next_position) then
            local next = index_grid(grid, next_position)

            if next.garden == garden and not next.visited then
                table.insert(region, {
                    garden=next.garden,
                    coord=next_position
                })

                region = search(grid, next_position, garden, region)
            end
        end
    end

    return region
end

local function calculate_perimeter(region)
    local perimeter = 0

    for _,g1 in ipairs(region) do
        local neighbors = 0;
        for _,g2 in ipairs(region) do
            if g1 ~= g2 and manhattan_distance(g1.coord, g2.coord) == 1 then
                neighbors = neighbors + 1
            end
        end
        perimeter = perimeter + (4 - neighbors)
    end

    -- print("Region " .. region[1].garden .. " perimeter: " .. perimeter)
    return perimeter
end

local function part1()
    local grid = read_file.parse("input.txt", parse_line)
    -- print_grid(grid)

    local regions = {}
    for y = 1, #grid do
        for x = 1, #grid[1] do
            if not grid[y][x].visited then
                local garden = grid[y][x].garden;
                local coord = {y, x}
                local region = {
                    {
                        garden=garden,
                        coord=coord
                    }
                }

                table.insert(regions, search(grid, coord, garden, region))
            end
        end
    end

    local price = 0
    for _,region in ipairs(regions) do
        -- print("Garden " .. region[1].garden .. " Size: " .. #region)
        price = price + calculate_perimeter(region) * #region
    end
    return price
end

local function part2()
    print(0)
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 1387004, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
