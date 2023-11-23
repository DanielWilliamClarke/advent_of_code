#ifndef SOLUTION_H
#define SOLUTION_H
#pragma once

#include <string>
#include <vector>

template <typename Input, typename Output1, typename Output2 = Output1>
class Solution {
public: 
    virtual std::string filename () const = 0;
    virtual Output1 part1 (std::vector<Input> input) const = 0;
    virtual Output2 part2 (std::vector<Input> input) const = 0;
};

#endif // SOLUTION_H