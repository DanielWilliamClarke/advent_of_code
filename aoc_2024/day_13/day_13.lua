package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function print_games(games)
    print("total games " .. #games)

    for _,g in ipairs(games) do 
        print("A" .. " X: " .. g["A"].x .. ", " .. g["A"].y)
        print("B" .. " X: " .. g["B"].x .. ", " .. g["B"].y)
        print("Prize" .. " X: " .. g["Prize"].x .. ", " .. g["Prize"].y)
        print("-------------------")
    end
end

local function parse_games(program, prize_floor)
    local pre_parsed_games = {}

    local current_game = {}
    for i,line in ipairs(program) do
        if i % 4 ~= 0 then
            table.insert(current_game, line)
        else 
            table.insert(pre_parsed_games, current_game)
            current_game = {}
        end
    end
    table.insert(pre_parsed_games, current_game)

    local games = {}
    for _,g in ipairs(pre_parsed_games) do
        local game = {}
        local aX, aY = string.match(g[1], 'X%+(%d+), Y%+(%d+)')
        game["A"] = {
            x=tonumber(aX),
            y=tonumber(aY)
        }
        local bX, bY = string.match(g[2], 'X%+(%d+), Y%+(%d+)')
        game["B"] = {
            x=tonumber(bX),
            y=tonumber(bY)
        }
        local pX, pY = string.match(g[3], 'X=(%d+), Y=(%d+)')
        game["P"] = {
            x=tonumber(pX) + prize_floor,
            y=tonumber(pY) + prize_floor
        }

        table.insert(games, game)
    end

    return games
end

local function is_integer(n)
    return n % 1 == 0
end

-- https://en.wikipedia.org/wiki/Cramer%27s_rule
local function find_min_tokens(game)
    local a = game["A"];
    local b = game["B"];
    local p = game["P"];

    local det = a.x * b.y - a.y * b.x
    if det == 0 then
        return 0
    end

    local a_presses = (p.x * b.y - p.y * b.x) / det
    local b_presses = (a.x * p.y - p.x * a.y) / det

    if is_integer(a_presses) and is_integer(b_presses) then
        return (3 * a_presses) + b_presses
    end

    return 0
end

local function part1()
    local program =
        read_file.parse(
            "input.txt",
            function(line)
                return line
            end
        )

    local games = parse_games(program, 0)
    -- print_games(games)

    local tokens = 0
    for _,g in ipairs(games) do
        tokens = tokens + find_min_tokens(g)
    end
    return tokens
end

local function part2()
    local program =
    read_file.parse(
        "input.txt",
        function(line)
            return line
        end
    )

    local games = parse_games(program, 1e13)
    -- print_games(games)

    local tokens = 0
    for _,g in ipairs(games) do
        tokens = tokens + find_min_tokens(g)
    end
    return tokens
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 37901, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 77407675412647, "Part 2 solution incorrect!")
    end
)
