#ifndef AOC_2023_CONSTRAINTS_H
#define AOC_2023_CONSTRAINTS_H

#include <iostream>

template <typename T>
concept Streamable = requires (T t)
{
    std::cout << t;
};

template <typename T>
concept Readable = requires(std::istream &os, T value)
{
    { os >> value } -> std::convertible_to<std::istream &>;
};

#endif //AOC_2023_CONSTRAINTS_H
