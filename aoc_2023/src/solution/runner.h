#ifndef RUNNER_H
#define RUNNER_H
#pragma once

#include <vector>
#include <memory>
#include "printer.h"

void run(std::vector<std::unique_ptr<Printer>>& days);

#endif // RUNNER_H