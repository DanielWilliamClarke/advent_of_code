#ifndef DAY_15_H
#define DAY_15_H

#include <map>
#include <ranges>

#include "main/solution/day.h"

struct Sequence {
    std::string label;
    int focalLength;

    Sequence(std::string label, int focalLength)
        : label(label), focalLength(focalLength)
    {}
};

struct Box {
    std::vector<Sequence> lenses;

    Box();
    void removeLens(const std::string& label);
    void addLens(const Sequence& sequence);
};

int computeHash(const std::string& label);

// Part 2
std::vector<std::shared_ptr<Box>> generateBoxes(int total);
void parseAndProcessBoxes(const std::vector<std::shared_ptr<Box>>& boxes, const std::string& input);
int focusLenses(const std::vector<std::shared_ptr<Box>>& boxes);

class Day15 : public Day<int>
{
public:
    virtual ~Day15() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_15_H