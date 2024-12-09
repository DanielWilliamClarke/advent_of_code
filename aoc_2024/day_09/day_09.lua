package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function print_disk(disk)
    for _, v in ipairs(disk) do
        if v == false then
            io.write(".")
        else
            io.write(v)
        end
    end
    io.write("\n")
end

local function unpacked_blocks(disk_map)
    local blocks = {}
    local index = 1
    local id = 0
    for c in string.gmatch(disk_map, ".") do
        local total_blocks = tonumber(c)

        local block = false
        if index % 2 ~= 0 then
            block = id
            id = id + 1
        end

        for i = 1, total_blocks do
            table.insert(blocks, block)
        end

        index = index + 1
    end
    return blocks
end

local function defrag(disk)
    for i = 1, #disk do
        -- walk up the disk find each free space
        if disk[i] == false then
            -- walk backwards from the end of the disk
            -- swap first not empty block with empty block
            for j = #disk, 1, -1 do
                if j < i then
                    goto finish
                end

                if disk[j] ~= false then
                    disk[i] = disk[j]
                    disk[j] = false
                    -- print_disk(disk)
                    goto continue
                end
            end
        end
        ::continue::
    end
    ::finish::
    return disk
end

local function calculate_checksum(disk)
    local checksum = 0
    for i = 1, #disk do
        if disk[i] == false then
           goto finish
        end
        checksum = checksum + ((i - 1) * disk[i])
    end
    ::finish::
    return checksum
end

local function part1()
    local disk = read_file.parse("input.txt", unpacked_blocks)[1]
    -- print_disk(disk)

    local defragged_disk = defrag(disk)
     -- print_disk(disk)

    local checksum = calculate_checksum(disk)
    -- print(checksum)

    return checksum
end

local function part2()
    print(0)
    return 0
end

test(
    "🎅 Part 1",
    function(a)
        a.ok(timing.measure(part1) == 6241633730082, "Part 1 solution incorrect!")
    end
)

test(
    "🎄 Part 2",
    function(a)
        a.ok(timing.measure(part2) == 0, "Part 2 solution incorrect!")
    end
)
