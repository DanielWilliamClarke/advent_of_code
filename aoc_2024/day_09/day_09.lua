package.path = package.path .. ";../utils/?.lua"

local test = require "simple_test"
local read_file = require "read_file"
local timing = require "timing"

local function print_disk(disk)
    for _, v in ipairs(disk) do
        if v == false then
            io.write(".")
        else
            io.write("[")
            io.write(v)
            io.write("]")
        end
    end
    io.write("\n")
end

local function unpacked_blocks(disk_map)
    local blocks, index, id = {}, 1, 0
    for b in string.gmatch(disk_map, ".") do
        local block = false
        if index % 2 ~= 0 then
            block = id
            id = id + 1
        end
        for i = 1, tonumber(b) do
            table.insert(blocks, block)
        end
        index = index + 1
    end
    return blocks
end

local function block_defrag(disk)
    for i = 1, #disk do
        if disk[i] == false then
            for j = #disk, 1, -1 do
                if j < i then
                    goto finish
                end
                if disk[j] ~= false then
                    disk[i] = disk[j]
                    disk[j] = false
                    goto continue
                end
            end
        end
        ::continue::
    end
    ::finish::
    return disk
end

local function find_space(disk, required_size, limit)
    local start_index, space_size, inside_space = 0, 0, false
    for i = 1, #disk do
        if i > limit then
            return nil
        end
        if disk[i] == false then
            if not inside_space then
                start_index = i
                inside_space = true
            end
            space_size = space_size + 1
        end
        if disk[i] ~= false and inside_space then
            inside_space = false
            if space_size < required_size then
                start_index = 0
                space_size = 0
            else
                return start_index
            end
        end
    end
    return nil
end

local function file_defrag(disk)
    local file, file_length = nil, 0
    for i = #disk, 1, -1 do
        if file ~= nil then
            if disk[i] == false or disk[i] ~= file then
                local space_index = find_space(disk, file_length, i + 1)
                if space_index ~= nil then
                    for j = 1, file_length do
                        disk[space_index + j - 1] = file
                        disk[i + j] = false
                    end
                end
                file = nil
                file_length = 0
            end
        end
        if disk[i] ~= false then
            file = disk[i]
            file_length = file_length + 1
        end
    end
    return disk
end

local function calculate_checksum(disk)
    local checksum = 0
    for i = 1, #disk do
        if disk[i] ~= false then
            checksum = checksum + ((i - 1) * disk[i])
        end
    end
    return checksum
end

local function part1()
    local disk = read_file.parse("input.txt", unpacked_blocks)[1]
    -- print_disk(disk)
    local defragged_disk = block_defrag(disk)
    -- print_disk(disk)
    return calculate_checksum(disk)
end

local function part2()
    local disk = read_file.parse("input.txt", unpacked_blocks)[1]
    -- print_disk(disk)
    local defragged_disk = file_defrag(disk)
    --print_disk(defragged_disk)
    return calculate_checksum(disk)
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
        a.ok(timing.measure(part2) == 6265268809555, "Part 2 solution incorrect!")
    end
)
