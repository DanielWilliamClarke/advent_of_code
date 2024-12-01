
local read_file = {}

local function file_exists(file)
  local f = io.open(file, "rb")
  if f then f:close() end
  return f ~= nil
end

-- get all lines from a file, returns an empty
-- list/table if the file does not exist
function read_file.parse(file, parser)
  local lines = {}
  for line in io.lines(file) do
      local data = parser(line)
      table.insert (lines, data)
  end
  return lines
end

return read_file
