#include "day_18.h"

#include <ranges>
#include <regex>
#include <numeric>
#include <sstream>

const std::regex regex(R"(([RDLU]) ([0-9]+) \(#(\w{6})\))");

std::vector<day18::Point> day18::parsePoints(const std::vector<std::string>& input)
{
    day18::Position lastPosition = { 0, 0 };

    auto points = input
        | std::views::transform([&lastPosition](const std::string& line) -> Point {
            std::smatch match;
            std::regex_search(line, match, regex);
            auto dir = match[1].str().c_str()[0];
            auto length = std::stoll(match[2].str());
            auto color =  match[3].str();

            Direction direction;
            switch (dir)
            {
                case 'R': {
                    direction = std::make_pair(1, 0);
                    break;
                }
                case 'D': {
                    direction = std::make_pair(0, 1);
                    break;
                }
                case 'L': {
                    direction = std::make_pair(-1, 0);
                    break;
                }
                case 'U': {
                    direction = std::make_pair(0, -1);
                    break;
                }
                // shouldn't happen
                default: exit(1);
            }

            day18::Position newPosition = {
                lastPosition.first + (direction.first * length),
                lastPosition.second + (direction.second * length)
            };
            lastPosition = newPosition;

            return {
                newPosition,
                direction,
                length,
                color
            };
        });

    return { points.begin(), points.end() };
}

std::vector<day18::Point> day18::parsePointsFromHex(const std::vector<std::string>& input)
{
    day18::Position lastPosition = { 0, 0 };

    auto points = input
          | std::views::transform([&lastPosition](const std::string& line) -> Point {
        std::smatch match;
        std::regex_search(line, match, regex);
        auto hex = match[3].str();

        // hex -> decimal
        long long length = 0;
        std::stringstream ss;
        ss << std::string({ hex.begin(), hex.end() - 1 });
        ss >> std::hex >> length;

        Direction direction;
        switch (hex.back() - 0x30)
        {
            case 0: {
                direction = std::make_pair(1, 0);
                break;
            }
            case 1: {
                direction = std::make_pair(0, 1);
                break;
            }
            case 2: {
                direction = std::make_pair(-1, 0);
                break;
            }
            case 3: {
                direction = std::make_pair(0, -1);
                break;
            }
            // shouldn't happen
            default: exit(1);
        }

        day18::Position newPosition = {
            lastPosition.first + (direction.first * length),
            lastPosition.second + (direction.second * length)
        };
        lastPosition = newPosition;

        return {
            newPosition,
            direction,
            length,
            hex
        };
    });

    return { points.begin(), points.end() };
}

// shoelace formula: calculate internal area of polygon with n points: https://en.wikipedia.org/wiki/Shoelace_formula
long long day18::shoelace(const std::vector<day18::Point>& points)
{
    long long leftSum = 0;
    long long rightSum = 0;

    for (int left = 0; left < points.size(); ++left)
    {
        auto right = (left + 1) % (int)points.size();
        leftSum += points[left].position.first * points[right].position.second;
        rightSum += points[right].position.first * points[left].position.second;
    }

    return std::abs(rightSum - leftSum) / 2;
}

long long day18::perimeter(const std::vector<day18::Point>& points)
{
    return std::transform_reduce(
        points.begin(),
        points.end(),
        0ll,
        std::plus<>(),
        [=](const day18::Point& p) { return p.length; }
    );
}

long long day18::calculateArea(const std::vector<Point>& points)
{
    auto area = day18::shoelace(points);
    auto perimeter = day18::perimeter(points);

    // picks theorem bro: https://en.wikipedia.org/wiki/Pick%27s_theorem
    return area + perimeter / 2 + 1;
}

constexpr std::string Day18::filename () const 
{
    return "main/days/18/input.txt";
}

long long Day18::part1(const std::vector<std::string>& input) const
{
    return day18::calculateArea(day18::parsePoints(input));
}

long long Day18::part2(const std::vector<std::string>& input) const
{
    return day18::calculateArea(day18::parsePointsFromHex(input));
}