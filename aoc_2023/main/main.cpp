#include <iostream>
#include <iomanip>
#include <memory>

#include "main/solution/printer.h"
#include "main/solution/runner.h"

#include "main/days/00/day_00.h"

int main () 
{
    run({
        std::make_shared<Day00>()
    });
}