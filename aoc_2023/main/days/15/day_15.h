#ifndef DAY_15_H
#define DAY_15_H

#include <map>
#include <ranges>

#include "main/solution/day.h"

constexpr int BUCKETS = 256;

struct Box {
    std::vector<std::pair<std::string, std::string>> lenses;

    Box();
    void removeLens(const std::string& label);
    void addLens(const std::pair<std::string, std::string>& sequence);
};

using HashMap = std::array<std::shared_ptr<Box>, BUCKETS>;

int computeHash(const std::string& label);

// Part 2
HashMap generateBoxes();
void parseAndProcessBoxes(HashMap boxes, const std::string& input);
int focusLenses(HashMap boxes);

class Day15 : public Day<int>
{
public:
    virtual ~Day15() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_15_H