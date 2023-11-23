#include <iostream>
#include <iomanip>
#include <memory>

#include "solution/printer.h"
#include "days/00/day_00.h"

int main () {
    Day00 day00(std::make_unique<SolutionPrinter<int>>());

    day00.print();

    std::cout << "Hello World" << std::endl;
}