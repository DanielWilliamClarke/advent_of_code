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

local function rotate_vector(coord, clockwise)
    -- coord is { y , x }
    if clockwise then
        return {coord[2], -coord[1]} -- x, -y
    else
        return {-coord[2], coord[1]} -- -x, y
    end
end


local function count_sides(region)
    if #region == 1 then 
        -- print("Region " .. region[1].garden .. " sides: " .. 4)
        return 4 
    end

    local sides = 1
    local regionSet = {}

    for _, garden in ipairs(region) do
        regionSet[garden.coord[1] .. "," .. garden.coord[2]] = true
    end

    local origin = region[1].coord
    local current = { origin[1],origin[2] }
    local dir_normal = { -1, 0 } -- up
    local dir_forward = rotate_vector(dir_normal, true) -- right
    local initial_dir_forward = { dir_normal[1], dir_normal[2] } 

    repeat 
        -- print("Region " .. region[1].garden .. " current: " .. current[1] .. "," .. current[2] .. " direction: " .. dir_forward[1] .. "," .. dir_forward[2] .. " sides " .. sides)

        -- lets have two vectors 90 degrees from each other 
        -- if going right -> then we should have another perpendicular
        -- keep checking each square
        local look_normal = {  -- look perpendicular to direction of travel
            current[1] + dir_normal[1],
            current[2] + dir_normal[2]
        }
        local look_forward = {  -- look in direction of travel
            current[1] + dir_forward[1],
            current[2] + dir_forward[2]
        }

        local rotated = false
        if regionSet[look_normal[1] .. "," .. look_normal[2]] then
            -- increment sides now we need to change direction
            -- rotate anti-clockwise
            dir_normal = rotate_vector(dir_normal)
            dir_forward = rotate_vector(dir_forward)
            rotated = true
            look_forward = {  -- look in direction of travel
                current[1] + dir_forward[1],
                current[2] + dir_forward[2]
            }
        elseif not regionSet[look_forward[1] .. "," .. look_forward[2]] then
            -- increment sides now we need to change direction
            -- rotate clockwise 
            dir_normal = rotate_vector(dir_normal, true)
            dir_forward = rotate_vector(dir_forward, true)
            rotated = true
            look_forward = {  -- look in direction of travel
                current[1] + dir_forward[1],
                current[2] + dir_forward[2]
            }
        end
        
        if regionSet[look_forward[1] .. "," .. look_forward[2]]then
            -- move in direction of travel fine
            current = look_forward
        end

        if rotated then 
            sides = sides + 1
        end 
    until (
        current[1] == origin[1] and
        current[2] == origin[2] and
        dir_forward[1] == initial_dir_forward[1] and
        dir_forward[2] == initial_dir_forward[2]
        -- back at origin and direction is going up
    )

    -- print("Region " .. region[1].garden .. " | sides: " .. sides .. " | dir: " .. dir_forward[1] .. " , " .. dir_forward[2])

    return sides
end

local function flood_fill(grid, regionSet, visited, stack, mark_external)
    local holePoints = {}
    while #stack > 0 do
        local current = table.remove(stack)
        -- print("Stack size " .. #stack .. " | Current " .. current[1] .. " , " .. current[2])

        local key = current[1] .. "," ..  current[2]
        if within_bounds(grid, current) and not visited[key] and not regionSet[key] then
            visited[key] = mark_external and "external" or "hole"
            table.insert(holePoints, {
                garden=".",
                coord=current
            })

            for _, dir in ipairs(directions) do
                local next = {
                    current[1] + dir[1], 
                    current[2] + dir[2]
                }

                if within_bounds(grid, next) and not visited[next[1] .. "," .. next[2]] then
                    table.insert(stack, next)
                end
            end
        end
    end
    return holePoints
end

local function count_sides_with_holes(grid, region)
    -- Calculate sides of the main region
    local sides = count_sides(region)
    -- print("Garden " .. region[1].garden .. " Sides: " .. sides)

    -- Create a set of all grid points in the region
    local regionSet = {}
    local visited = {}
    local gridHeight = #grid
    local gridWidth = #grid[1]

    for _, garden in ipairs(region) do
        regionSet[garden.coord[1] .. "," .. garden.coord[2]] = true
    end
   
    for y = 1, gridHeight do
        for _, x in ipairs({1, gridWidth}) do
            local key = y .. "," .. x
            if not visited[key] and not regionSet[key] then
                flood_fill(grid, regionSet, visited, {{y, x}}, true)
            end
        end
    end
    for x = 1, gridWidth do
        for _, y in ipairs({1, gridHeight}) do
            local key = y .. "," .. x
            if not visited[key] and not regionSet[key] then
                flood_fill(grid, regionSet, visited, {{y, x}}, true)
            end
        end
    end

    local holeSides = 0
    for y = 1, gridHeight do
        for x = 1, gridWidth do
            local key = y .. "," .. x
            if not visited[key] and not regionSet[key] then
                local holePoints = flood_fill(grid, regionSet, visited, {{y, x}})
                if #holePoints > 0 then
                    holeSides = holeSides + count_sides(holePoints)
                end
            end
        end
    end

    -- Total sides = region sides + hole sides
    print("Region sides " .. region[1].garden .. " (including holes): " .. (sides + holeSides))
    return sides + holeSides
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

local function part2(input_file)
    local grid = read_file.parse(input_file, parse_line)
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
        price = price + count_sides_with_holes(grid, region) * #region
    end
    return price
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 1387004, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2 Example 1",
    function(a)
        a.ok(timing.measure(function() return part2("example_1.txt") end) == 236, "Part 2 solution incorrect!")
    end
)

test(
    "🎄 Part 2 Example 2",
    function(a)
        a.ok(timing.measure(function() return part2("example_2.txt") end) == 368, "Part 2 solution incorrect!")
    end
)

test(
    "🎄 Part 2 Example 3",
    function(a)
        a.ok(timing.measure(function() return part2("example.txt") end) == 1206, "Part 2 solution incorrect!")
    end
)

test(
    "🎅 Part 2 Input",
    function(a)
        a.ok(timing.measure(function() return part2("input.txt") end) == 0, "Part 2 solution incorrect!")
    end
)