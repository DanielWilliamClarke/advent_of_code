#ifndef DAY_13_H
#define DAY_13_H

#include "main/solution/day.h"

std::vector<std::vector<std::string>> parseLandscapes(const std::vector<std::string>& input);
int countInconsistencies(const std::string& rowUp, const std::string& rowDown);
std::vector<std::string> flipLandscape(const std::vector<std::string>& landscape);
int findReflection(const std::vector<std::string>& landscape, int threshold = 0);

class Day13 : public Day<int>
{
public:
    virtual ~Day13() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_13_H