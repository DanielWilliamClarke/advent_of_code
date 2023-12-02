#ifndef AOC_2023_CONSTRAINTS_H
#define AOC_2023_CONSTRAINTS_H

#include <iostream>

template <typename T>
concept Streamable = requires (T t)
{
    std::cout << t;
};

#endif //AOC_2023_CONSTRAINTS_H
