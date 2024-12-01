local socket = require("socket")

local timing = {}

function timing.measure (cb)
    local start_time = socket.gettime()
    local result = cb()
    local elapsed_time = (socket.gettime() - start_time)

    print(string.format("Elapsed time: %.6f s", elapsed_time))
    return result
end

return timing
