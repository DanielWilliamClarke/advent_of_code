#ifndef AOC_2023_MEASURER_H
#define AOC_2023_MEASURER_H

#include <chrono>
#include <functional>
#include <utility>

#include "constraints.h"

class Measurer
{
public:
    template<Streamable Output>
    std::pair<Output, float> measure(std::function<Output()> method) const;
};

template <Streamable Output>
std::pair<Output, float> Measurer::measure(std::function<Output()> method) const {
    std::chrono::duration<float> duration(0.0f);

    auto start = std::chrono::high_resolution_clock::now();
    auto output = method();
    auto end = std::chrono::high_resolution_clock::now();

    duration = (end - start);

    return std::make_pair(
        output,
        duration.count()
    );
}

#endif //AOC_2023_MEASURER_H
