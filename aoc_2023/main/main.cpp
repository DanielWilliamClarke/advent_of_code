#include <iostream>
#include <iomanip>
#include <memory>

#include <range/v3/all.hpp>

#include "main/solution/printer.h"

#include "main/days/00/day_00.h"

int main () 
{
    auto days = {
        std::make_shared<Day00>()
    };

    ranges::for_each(days, [=] (auto day) { day->run(); });
}