#ifndef RUNNER_H
#define RUNNER_H
#pragma once

#include <vector>
#include <memory>

#include "printer.h"

auto run(const std::vector<std::shared_ptr<Printer>> days) {
    std::for_each(days.cbegin(), days.cend(), [=] (const std::shared_ptr<Printer> day) {
        day->print();
    });
}

#endif // RUNNER_H