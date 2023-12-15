#include "day_15.h"

#include <ranges>
#include <numeric>
#include <algorithm>
#include <optional>

#include "main/solution/string_utils.h"

void Box::removeLenseByLabel(std::string label)
{
    auto [start, end] = std::ranges::remove_if(
            this->lenses,
            [&label](auto s) { return s.label == label; }
    );

    this->lenses.erase(start, end);
}

void Box::addLense(Sequence sequence)
{
    auto lenseIter = std::ranges::find_if(
            this->lenses,
            [&sequence](auto s) { return s.label == sequence.label; }
    );

    if (lenseIter != this->lenses.end())
    {
        // replace lense if label is present
        lenseIter->focalLength = sequence.focalLength;
    }
    else
    {
        // add lense to the bacl
        this->lenses.push_back(sequence);
    }
}

std::vector<std::string> parseInitializationSequence(const std::string& input)
{
    return splitString(input,  ',');
}

std::vector<Sequence> parseSequenceCommands(const std::string& input)
{
    auto commands = splitString(input,  ',')
        | std::views::transform([=](const std::string& sequence) -> Sequence {
            auto parts = splitString(sequence,  '=');

            if (parts.size() == 1) {
                return {
                    { parts.front().begin(), parts.front().end() - 1 },
                    Operation::DASH,
                    -1
                };
            } else {
                return {
                    parts.front(),
                    Operation::EQUALS,
                    std::stoi(parts.back())
                };
            }
        });

    return { commands.begin(), commands.end() };
}

int computeHash(const std::string& label)
{
    auto hash = 0;

    for(const auto& c : label)
    {
        hash += c;
        hash *= 17;
        hash %= 256;
    }

    return hash;
}

std::vector<int> computeHashes(const std::vector<std::string>& sequences)
{
    auto hashes = sequences
        | std::views::transform([=](const std::string& sequence) -> int {
            return computeHash(sequence);
        });

    return { hashes.begin(), hashes.end() };
}

std::vector<std::shared_ptr<Box>> generateBoxes(int total)
{
    std::vector<std::shared_ptr<Box>> boxes;
    boxes.reserve(total);

    for(auto i = 0; i < total; i++)
    {
        boxes.emplace_back(std::make_shared<Box>(i));
    }

    return boxes;
}

std::vector<std::shared_ptr<Box>> processBoxes(const std::vector<std::shared_ptr<Box>>&  boxes, const std::vector<Sequence>& commands)
{
    auto filledBoxes = boxes;

    for (auto command : commands)
    {
        auto hash = computeHash(command.label);
        auto box = filledBoxes.at(hash);

        switch (command.operation)
        {
            case Operation::DASH: {
                // go to box at hash and remove lense with label
                box->removeLenseByLabel(command.label);
                break;
            }
            case Operation::EQUALS: {
                // go box and add focal length
                box->addLense(command);
                break;
            }
        }
    }

    return filledBoxes;
}

int focusLenses(const std::vector<std::shared_ptr<Box>>& boxes)
{
    int focus = 0;

    for (auto boxId = 0; boxId < boxes.size(); boxId++)
    {
        const auto& box = boxes[boxId];

        for (auto i  = 0; i < box->lenses.size(); i++)
        {
            focus += (boxId + 1) * (i + 1) * box->lenses[i].focalLength;
        }
    }

    return focus;
}

constexpr std::string Day15::filename () const 
{
    return "main/days/15/input.txt";
}

int Day15::part1(const std::vector<std::string>& input) const
{
    auto sequences = parseInitializationSequence(input.front());

    auto hashes = computeHashes(sequences);

    return std::accumulate(
        hashes.begin(),
        hashes.end(),
        0,
        std::plus<>()
    );
}

int Day15::part2(const std::vector<std::string>& input) const 
{
    auto commands = parseSequenceCommands(input.front());

    auto boxes = generateBoxes(256);

    auto filledBoxes = processBoxes(boxes, commands);

    return focusLenses(boxes);
}