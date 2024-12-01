package = "aoc_2024"
version = "dev-1"
source = {
   url = "git+https://github.com/DanielWilliamClarke/advent_of_code.git"
}
description = {
   homepage = "https://github.com/DanielWilliamClarke/advent_of_code",
   license = "MIT"
}
dependencies = {
   "lua ~> 5.4",
   "luasocket",
   "simple_test"
}
build = {
   type = "builtin",
   modules = {}
}
