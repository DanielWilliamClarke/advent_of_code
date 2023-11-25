
#ifndef CARTESIAN_PRODUCT_H
#define CARTESIAN_PRODUCT_H
#pragma once

#include <vector>
#include <utility> 

template<typename Range1, typename Range2>
auto cartesian_product(const Range1& range1, const Range2& range2) {
    using ValueType1 = typename Range1::value_type;
    using ValueType2 = typename Range2::value_type;

    std::vector<std::pair<ValueType1, ValueType2>> result;

    for (const auto& elem1 : range1) {
        for (const auto& elem2 : range2) {
            result.push_back({elem1, elem2});
        }
    }

    return result;
}

#endif // CARTESIAN_PRODUCT_H
