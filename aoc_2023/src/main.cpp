#include <iostream>
#include <iomanip>
#include <memory>

#include "src/solution/printer.h"
#include "src/solution/runner.h"

#include "src/days/00/day_00.h"

int main () 
{
    run({
        std::make_shared<Day00>()
    });
}