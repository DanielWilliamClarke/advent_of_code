
local read_file = {}

function read_file.parse(file, parser)
  local lines = {}
  for line in io.lines(file) do
      local data = parser(line)
      table.insert (lines, data)
  end
  return lines
end

return read_file
