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

local function parse_games(program)
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
        game["Prize"] = {
            x=tonumber(pX),
            y=tonumber(pY)
        }

        table.insert(games, game)
    end

    return games
end

local function part1()
    local program =
        read_file.parse(
            "example.txt",
            function(line)
                return line
            end
        )

    local games = parse_games(program)
    print_games(games)

    print(0)
    return 0
end

local function part2()
    print(0)
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 0, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
