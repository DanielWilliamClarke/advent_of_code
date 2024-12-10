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

local function block_defrag(disk)
    for i = 1, #disk do
        -- walk up the disk find each free space
        if disk[i] == false then
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

local function find_space(disk, required_size, limit)
    local space_start_index = 0
    local space_size = 0
    local inside_space = false

    for i = 1, #disk do
        if i > limit then
            break
        end

        if disk[i] == false then
            if not inside_space then
                space_start_index = i
                inside_space = true
            end
             space_size = space_size + 1
        end

        if disk[i] ~= false and inside_space then
            inside_space = false
            if space_size < required_size then
                space_start_index = 0
                space_size = 0
            else
                return space_start_index
            end
        end
    end
    return nil
end

local function file_defrag(disk)
    local current_file = nil
    local current_file_length = 0

    for i = #disk, 1, -1 do
        if disk[i] == false or (current_file ~= nil and disk[i] ~= current_file) then
            local space_start_index = find_space(disk, current_file_length, i + 1)
            if space_start_index ~= nil then
                for j = 1, current_file_length do
                    disk[space_start_index + j - 1] = current_file
                    disk[i + j] = false
                end
                --print_disk(disk)
            end
            current_file = nil
            current_file_length = 0
        end

        if disk[i] ~= false then
            current_file = disk[i]
            current_file_length = current_file_length + 1
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
