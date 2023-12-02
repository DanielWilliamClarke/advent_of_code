#ifndef DAY_02_H
#define DAY_02_H

#include "main/solution/day.h"

struct Handful {
    int red;
    int green;
    int blue;

    Handful()
        : red(0), green(0), blue(0)
    {}

    Handful(int r, int g, int b)
            : red(r), green(g), blue(b)
    { }
};

struct Game {
    int id;
    std::vector<Handful> handfuls;

    Game(int id, std::vector<Handful> handfuls)
            : id(id), handfuls(handfuls)
    { }
};

std::vector<std::string> splitString(const std::string& str, char delim);
int extractNumber(const std::string& game);
std::vector<Handful> parseHandfuls(const std::string& str);
Game parseGameString (const std::string& str);

class Day02 : public Day<int>
{
public:
    virtual ~Day02() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_02_H