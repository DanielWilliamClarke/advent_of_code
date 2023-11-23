#include <iostream>
#include <iomanip>
#include <memory>

#include "solution/printer.h"
#include "solution/runner.h"

#include "days/00/day_00.h"

int main () {
    run({
        std::make_shared<Day00>()
    });
}