#ifndef RUNNER_H
#define RUNNER_H
#pragma once

#include <vector>
#include <memory>

#include "printer.h"

void run(std::vector<std::shared_ptr<Printer>> days) {
    std::for_each(days.begin(), days.end(), [=] (std::shared_ptr<Printer> day) {
        day->print();
    });
}

#endif // RUNNER_H