#include "day_16.h"

#include <ranges>

#define GRAY_COLOR "\033[38;5;8m"
#define RESET_COLOR "\033[0m"

day16::Contraption day16::parseContraption(const std::vector<std::string>& input)
{
    auto contraption = input
        | std::views::transform([=](const std::string& line) -> std::vector<std::shared_ptr<day16::ContraptionPart>> {
            auto parts = line
                | std::views::transform([=](const char& part) -> std::shared_ptr<day16::ContraptionPart> {
                    return std::make_shared<day16::ContraptionPart>(ContraptionPart(
                        static_cast<day16::ContraptionPartType>(part)
                    ));
                });

            return { parts.begin(), parts.end() };
        });

    return { contraption.begin(), contraption.end() };
}

bool day16::withinBounds(const day16::Contraption& contraption, const day16::StartPosition& position)
{
    return position.second >= 0 &&
        position.second < contraption.size() &&
        position.first >= 0 &&
        position.first < contraption[0].size();
}

day16::RayDirection day16::mirrorDirection(const day16::RayDirection& direction, day16::ContraptionPartType mirror)
{
    if(direction.first != 0)
    {
        switch(mirror)
        {
            case day16::ContraptionPartType::MIRROR_RIGHT: {
                return { 0, -direction.first };
            }
            case day16::ContraptionPartType::MIRROR_LEFT: {
                return { 0, direction.first };
            }
            default: return direction;
        }
    }

    if (direction.second != 0)
    {
        switch(mirror)
        {
            case day16::ContraptionPartType::MIRROR_RIGHT: {
                return { -direction.second, 0  };
            }
            case day16::ContraptionPartType::MIRROR_LEFT: {
                return { direction.second, 0 };
            }
            default: return direction;
        }
    }

    return direction;
}

std::vector<day16::RayDirection> day16::splitDirection(const day16::RayDirection& direction, day16::ContraptionPartType splitter)
{
    if(direction.first != 0)
    {
        switch(splitter)
        {
            case day16::ContraptionPartType::SPLITTER_UP_DOWN: {
                return {
                    { 0, -1 },
                    { 0, 1 }
                };
            }
            default: return { direction };
        }
    }

    if (direction.second != 0)
    {
        switch(splitter)
        {
            case day16::ContraptionPartType::SPLITTER_LEFT_RIGHT: {
                return {
                    { -1, 0 },
                    { 1, 0 }
                };
            }
            default: return { direction };
        }
    }

    return { direction };
}

day16::StartPosition day16::calculateNextPoint(const day16::StartPosition& position, const day16::RayDirection& direction)
{
    return {
        position.first + direction.first,
        position.second + direction.second
    };
}

void day16::traceContraption(
    day16::Contraption& contraption,
    const day16::StartPosition& position,
    const day16::RayDirection& direction
)
{
    // bounds check
    if (!day16::withinBounds(contraption, position))
    {
        return;
    }

    auto currentPart = contraption[position.second][position.first];
    currentPart->passes += 1;

    switch(currentPart->type)
    {
        case day16::ContraptionPartType::SPACE:
        {
            auto nextPosition = calculateNextPoint(position, direction);
            traceContraption(contraption, nextPosition, direction);
            break;
        }
        case day16::ContraptionPartType::MIRROR_RIGHT:
        case day16::ContraptionPartType::MIRROR_LEFT:
        {
            auto nextDirection = mirrorDirection(direction, currentPart->type);
            auto nextPosition = calculateNextPoint(position, nextDirection);
            traceContraption(contraption, nextPosition, nextDirection);
            break;
        }
        case day16::ContraptionPartType::SPLITTER_UP_DOWN:
        case day16::ContraptionPartType::SPLITTER_LEFT_RIGHT:
        {
            if (currentPart->passes > 1)
            {
                return;
            }

            for(auto nextDirection : splitDirection(direction, currentPart->type))
            {
                auto nextPosition = calculateNextPoint(position, nextDirection);
                traceContraption(contraption, nextPosition, nextDirection); // recurse one way
            }
            break;
        }
    }
}

int day16::calculateEnergisement(const day16::Contraption& contraption)
{
    auto total = 0;

    for(const auto& row : contraption)
    {
        for (const auto& col : row)
        {
            if (col->passes != 0)
            {
                total += 1;
            }
        }
    }

    return total;
}

day16::Contraption& day16::refreshContraption(day16::Contraption& contraption)
{
    for(const auto& row : contraption)
    {
        for (const auto& col : row)
        {
            col->passes = 0;
        }
    }

    return contraption;
}

constexpr std::string Day16::filename () const 
{
    return "main/days/16/input.txt";
}

int Day16::part1(const std::vector<std::string>& input) const
{
    auto contraption = day16::parseContraption(input);

    traceContraption(
        contraption,
        { 0, 0 },
        { 0, 1 }
    );

    for(const auto& row : contraption)
    {
        for (const auto& col : row)
        {
            if (col->passes != 0)
            {
                auto color = "\033[38;5;" + std::to_string(col->passes) + "m";
                std::cout << color <<  col->passes << RESET_COLOR;
            }
            else
            {
                std::cout << GRAY_COLOR << '.' << RESET_COLOR;
            }
        }

        std::cout << std::endl;
    }

    return calculateEnergisement(contraption);
}

int Day16::part2(const std::vector<std::string>& input) const 
{
    auto contraption = day16::parseContraption(input);

    std::vector<int> energies;

    for (auto y = 0; y < contraption.size(); y++)
    {
        // left
        traceContraption(
                refreshContraption(contraption),
                { 0, y },
                { 1, 0 }
        );
        energies.push_back(calculateEnergisement(contraption));

        // right
        traceContraption(
                refreshContraption(contraption),
                { contraption[0].size() - 1, y},
                { -1, 0 }
        );
        energies.push_back(calculateEnergisement(contraption));
    }

    for (auto x = 0; x < contraption[0].size(); x++)
    {
        // top
        traceContraption(
            refreshContraption(contraption),
            { x, 0 },
            { 0, 1 }
        );
        energies.push_back(calculateEnergisement(contraption));

        // bottom
        traceContraption(
            refreshContraption(contraption),
            { x, contraption.size() - 1 },
            { 0, -1 }
        );
        energies.push_back(calculateEnergisement(contraption));
    }

    return *std::ranges::max_element(energies);
}