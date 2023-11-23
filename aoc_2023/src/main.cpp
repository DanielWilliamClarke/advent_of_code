#include <iostream>
#include <iomanip>

#include "example/example.h"
#include "days/00/day_00.h"

int main () {
    Day00 day00;

    auto input = std::vector<int>{ 1, 2, 3 };

    std::cout << day00.filename() << std::endl;
    std::cout << day00.part1(input) << std::endl;
    std::cout << day00.part2(input) << std::endl;

    std::cout << "Hello World" << std::endl;
}