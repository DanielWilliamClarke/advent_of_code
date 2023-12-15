#ifndef DAY_15_H
#define DAY_15_H

#include <map>
#include <ranges>

#include "main/solution/day.h"

enum Operation {
    DASH = '-',
    EQUALS = '='
};

struct Sequence {
    std::string label;
    Operation operation;
    int focalLength;

    Sequence(std::string label, Operation operation, int focalLength)
        : label(label), operation(operation), focalLength(focalLength)
    {}
};

struct Box {
    int id;
    std::vector<Sequence> lenses;

    Box(int id)
        : id(id)
    {}

    void removeLens(std::string label);
    void addLens(Sequence sequence);
};

int computeHash(const std::string& label);

// Part 1
int computeHashSum(const std::vector<std::string>& sequences);

// Part 2
std::vector<Sequence> parseSequenceCommands(const std::string& input);
std::vector<std::shared_ptr<Box>> generateBoxes(int total);
std::vector<std::shared_ptr<Box>> processBoxes(const std::vector<std::shared_ptr<Box>>& boxes, const std::vector<Sequence>& commands);
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