#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <vector>

#include "constraints.h"

template <Readable Input, Streamable Output1, Streamable Output2 = Output1>
class Solution
{
public:
    virtual Output1 part1(const std::vector<Input>&) const = 0;
    virtual Output2 part2(const std::vector<Input>&) const = 0;
};

#endif // SOLUTION_H