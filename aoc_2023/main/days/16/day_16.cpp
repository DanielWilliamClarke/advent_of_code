#include "day_16.h"

#include <ranges>

#define GRAY_COLOR "\033[38;5;8m"
#define RESET_COLOR "\033[0m"

Contraption parseContraption(const std::vector<std::string>& input)
{
    auto contraption = input
        | std::views::transform([=](const std::string& line) -> std::vector<std::shared_ptr<ContraptionPart>> {
            auto parts = line
                | std::views::transform([=](const char& part) -> std::shared_ptr<ContraptionPart> {
                    return std::make_shared<ContraptionPart>(ContraptionPart(
                        static_cast<ContraptionPartType>(part)
                    ));
                });

            return { parts.begin(), parts.end() };
        });

    return { contraption.begin(), contraption.end() };
}

bool withinBounds(const Contraption& contraption, const StartPosition& position)
{
    return position.second >= 0 &&
        position.second < contraption.size() &&
        position.first >= 0 &&
        position.first < contraption[0].size();
}

RayDirection mirrorDirection(const RayDirection& direction, ContraptionPartType mirror)
{
    if(direction.first != 0)
    {
        switch(mirror)
        {
            case ContraptionPartType::MIRROR_RIGHT: {
                return { 0, -direction.first };
            }
            case ContraptionPartType::MIRROR_LEFT: {
                return { 0, direction.first };
            }
            default: return direction;
        }
    }

    if (direction.second != 0)
    {
        switch(mirror)
        {
            case ContraptionPartType::MIRROR_RIGHT: {
                return { -direction.second, 0  };
            }
            case ContraptionPartType::MIRROR_LEFT: {
                return { direction.second, 0 };
            }
            default: return direction;
        }
    }

    return direction;
}

std::vector<RayDirection> splitDirection(const RayDirection& direction, ContraptionPartType splitter)
{
    if(direction.first != 0)
    {
        switch(splitter)
        {
            case ContraptionPartType::SPLITTER_UP_DOWN: {
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
            case ContraptionPartType::SPLITTER_LEFT_RIGHT: {
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

StartPosition calculateNextPoint(const StartPosition& position, const RayDirection& direction)
{
    return {
        position.first + direction.first,
        position.second + direction.second
    };
}

void traceContraption(
    Contraption& contraption,
    const StartPosition& position,
    const RayDirection& direction
)
{
    // bounds check
    if (!withinBounds(contraption, position))
    {
        return;
    }

    auto currentPart = contraption[position.second][position.first];
    currentPart->passes += 1;

    switch(currentPart->type)
    {
        case ContraptionPartType::SPACE:
        {
            auto nextPosition = calculateNextPoint(position, direction);
            traceContraption(contraption, nextPosition, direction);
            break;
        }
        case ContraptionPartType::MIRROR_RIGHT:
        case ContraptionPartType::MIRROR_LEFT:
        {
            auto nextDirection = mirrorDirection(direction, currentPart->type);
            auto nextPosition = calculateNextPoint(position, nextDirection);
            traceContraption(contraption, nextPosition, nextDirection);
            break;
        }
        case ContraptionPartType::SPLITTER_UP_DOWN:
        case ContraptionPartType::SPLITTER_LEFT_RIGHT:
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

int calculateEnergisement(Contraption& contraption)
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

Contraption& refreshContraption(Contraption& contraption)
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
    auto contraption = parseContraption(input);

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
    auto contraption = parseContraption(input);

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