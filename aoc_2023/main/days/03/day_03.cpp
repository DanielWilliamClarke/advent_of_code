#include "day_03.h"

#include <numeric>

bool validateEnginePart(const std::vector<std::string>& input, const Candidate& candidate)
{
    auto startX = candidate.start.x - 1;
    if (startX < 0) {
        startX = candidate.start.x;
    }
    auto endX = candidate.end.x + 1;
    if (endX >= input[0].size()) {
        endX = candidate.end.x;
    }

    auto startY = candidate.start.y - 1;
    if (startY < 0) {
        startY = candidate.start.y;
    }
    auto endY = candidate.end.y + 1;
    if (endY >= input.size()) {
        endY = candidate.end.y;
    }

    for (auto y = startY; y <= endY; y++) {
        for (auto x = startX; x <= endX; x++) {
            auto current = input[y][x];

            if (current == '.' || std::isdigit(current)) {
                continue;
            }

            return true;
        }
    }

    return false;
}

constexpr std::string Day03::filename () const 
{
    return "main/days/03/input.txt";
}

int Day03::part1(const std::vector<std::string>& input) const
{
    auto sum = 0;
    Candidate candidate;

    for(auto y = 0; y < input.size(); y++)
    {
        for(auto x = 0; x < input[y].size(); x++)
        {
            auto current = input[y][x];

            if (std::isdigit(current)) {
                if (candidate.number.empty()) {
                    candidate.start = Coordinate(x, y);
                }

                candidate.number.push_back(current);
            }

            if (!std::isdigit(current) || x + 1 >= input[y].size()) {
                if (!candidate.number.empty()) {
                    auto endX = x;
                    if (current == '.') {
                        endX = x - 1;
                    }

                    candidate.end = Coordinate(endX, y);

                    if(validateEnginePart(input, candidate)) {
                        sum += std::stoi(candidate.number);
                    }

                    candidate.number.clear();
                } else {
                    continue;
                }
            }
        }
    }

    return sum;
}

int Day03::part2(const std::vector<std::string>& input) const 
{
    return 0;
}