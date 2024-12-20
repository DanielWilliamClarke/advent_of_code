package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parse_robot(line)
    local robot = {}
    for p_x, p_y, v_x, v_y in string.gmatch(line, "p=(%d+),(%d+) v=([%-]?%d+),([%-]?%d+)") do
        robot = {
            p={x=tonumber(p_x), y=tonumber(p_y)},
            v={x=tonumber(v_x), y=tonumber(v_y)}
        }
    end
    return robot
end

local function print_robots(robots)
    for i, r in ipairs(robots) do 
        print ("Robot " .. i .. " Position " .. r.p.x .. ", " .. r.p.y .. " | Velocity " .. r.v.x .. ", " .. r.v.y)
    end
end

local function print_grid(robots, width, height)
    local robotSet = {}
    for _, r in ipairs(robots) do
        local key = r.p.x .. "," .. r.p.y;

        if not robotSet[key] then
            robotSet[key] = 1
        else 
            robotSet[key] = robotSet[key] + 1
        end
    end

    for y = 0, height - 1 do
        local row = {}

        for x = 0, width - 1 do

            local key = x .. "," .. y
            if not robotSet[key] then 
                table.insert(row, ".")
            else 
                table.insert(row, robotSet[key])
            end
        end

        print(table.concat(row, ""))
    end
end

local function simulate_moves(robots, width, height, iterations)
    local min_x = 0
    local max_x = width - 1

    local min_y = 0
    local max_y = height - 1

    print("tiles x " .. max_x .. " tiles y " .. max_y)

    for i = 1, iterations  do
        for _,r in ipairs(robots) do
            local next = {
                x=r.p.x + r.v.x,
                y=r.p.y + r.v.y
            }
            -- print ("Robot " .. i .. " Potential Next Position " .. next.x .. ", " .. next.y .. " | Velocity " .. r.v.x .. ", " .. r.v.y)

            -- bounds check 
            if next.x < min_x then 
                next.x = next.x + max_x + 1
            elseif next.x > max_x then 
                next.x = next.x - max_x - 1
            end
            if next.y < min_y then 
                next.y = next.y + max_y + 1
            elseif next.y > max_y then 
                next.y = next.y - max_y - 1
            end

            -- print ("Robot " .. i .. " Corrected Next Position " .. next.x .. ", " .. next.y .. " | Velocity " .. r.v.x .. ", " .. r.v.y)

            r.p = next
        end

        -- print ("Iteration " .. i)
        -- print_grid(robots, width, height)
        -- -- print_robots(robots)
        -- print("-------------------")
    end
end

local function bucket_robots (robots, width, height)
    local buckets = {
        tl={},
        tr={},
        bl={},
        br={}
    }

    local mid_width = math.floor(width / 2) 
    local mid_height = math.floor(height / 2)
    -- print("mid x " .. mid_width .. " mid y " .. mid_height)

    for i,r in ipairs(robots) do
        -- print ("Robot " .. i .. " Final Position " .. r.p.x .. ", " .. r.p.y)

        if r.p.x == mid_width or r.p.y == mid_height then
            goto continue
        end

        if r.p.x < mid_width and r.p.y < mid_height then
            table.insert(buckets.tl, r)
        elseif r.p.x > mid_width and r.p.y < mid_height then
            table.insert(buckets.tr, r)
        elseif r.p.x < mid_width and r.p.y > mid_height then
            table.insert(buckets.bl, r)
        elseif r.p.x > mid_width and r.p.y > mid_height then
            table.insert(buckets.br, r)
        end
        
        ::continue::
    end
    return buckets
end

local function part1()
    local width = 101
    local height = 103

    local robots = read_file.parse("input.txt", parse_robot)
    simulate_moves(robots, width, height, 100)

    local quadrants = bucket_robots(robots, width, height)
    
    local safety_factor = 1
    for _,q in pairs(quadrants) do
        safety_factor = safety_factor * math.max(#q, 1)
    end
    return safety_factor
end

local function part2()
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 225810288, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
