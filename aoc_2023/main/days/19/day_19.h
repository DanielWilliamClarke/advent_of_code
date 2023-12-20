#ifndef DAY_19_H
#define DAY_19_H

#include "main/solution/day.h"

namespace day19
{
    using Part = std::unordered_map<char, int>;

    using RuleEvaluator = std::function<bool(const Part&)>;
    using Rule = std::pair<RuleEvaluator, std::string>;

    struct Ruleset {
        std::string name;
        std::vector<Rule> rules;
        std::string defaultBucket;
    };

    size_t getSplitIndex(const std::vector<std::string>& input);
    Rule parseRule(const std::string& rule);
    std::unordered_map<std::string, day19::Ruleset> parseRules(const std::vector<std::string>& input);
    std::vector<Part> parseParts(const std::vector<std::string>& input);
    std::vector<Part> processParts(
        const std::unordered_map<std::string, day19::Ruleset>& rules,
        const std::vector<Part>& parts
    );

    int accumulatePartValues(const std::vector<Part>& parts);
}

class Day19 : public Day<int>
{
public:
    virtual ~Day19() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_19_H