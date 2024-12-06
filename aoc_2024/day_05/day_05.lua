package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function parse_rules_updates(lines)
    local rules = {}
    local updates = {}
    local split_detected = false

    for _, line in ipairs(lines) do
        if line == "" then
            split_detected = true
        elseif split_detected == false then
            table.insert(rules, line)
        elseif split_detected == true then
            local pages = {}
            for p in string.gmatch(line, "([^,]+)") do
                table.insert(pages, p)
            end
            table.insert(updates, pages)
        end
    end

    return rules, updates
end

local function is_in_rule_set(rules, first, second)
    for _, r in ipairs(rules) do
        if (r == first .. "|" .. second) then
            return true
        end
    end

    return false
end

local function part1()
    local lines =
        read_file.parse(
        "input.txt",
        function(line)
            return line
        end
    )

    local rules, updates = parse_rules_updates(lines)
    local total = 0

    for _, update in ipairs(updates) do
        for i = 2, #update do
            if not is_in_rule_set(rules, update[i - 1], update[i]) then
                goto continue
            end
        end

        total = total + update[math.ceil(#update / 2)]
        ::continue::
    end

    print(total)
    return total
end

local function part2()
    local lines =
        read_file.parse(
        "input.txt",
        function(line)
            return line
        end
    )

    local rules, updates = parse_rules_updates(lines)

    local incorrect_updates = {}
    for _,update in ipairs(updates) do
        local correct = true;

        for i = 2, #update do
            if not is_in_rule_set(rules, update[i - 1], update[i]) then
                correct = false
                goto continue
            end
        end

        ::continue::
        if not correct then
           table.insert(incorrect_updates, update)
        end
    end

    local total = 0
    for _,update in ipairs(incorrect_updates) do
         ::check_again::
         for i = 2, #update do
            -- check pair if in rule set
            if not is_in_rule_set(rules, update[i - 1], update[i]) then
                -- if not in rule set, check if swap is in rule set
                if is_in_rule_set(rules, update[i], update[i - 1]) then
                    -- swap the values and then recheck the whole update again
                    local temp =  update[i - 1]
                    update[i - 1] = update[i]
                    update[i] = temp
                    goto check_again
                else
                    -- if not in rule set at all ignore it
                    goto continue
                end
            end
         end

         total = total + update[math.ceil(#update / 2)]
         ::continue::
    end

    print(total)
    return total
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 4135, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 5285, "Part 2 solution incorrect!")
    end
)
