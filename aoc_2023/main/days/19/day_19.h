#ifndef DAY_19_H
#define DAY_19_H

#include "main/solution/day.h"

namespace day19
{
    enum PartType: char {
        X = 'x',
        M = 'm',
        A = 'a',
        S = 's',
    };

    using Part = std::unordered_map<PartType, long long>;
    using RuleEvaluator = std::function<bool(const Part&)>;

    struct Rule {
        PartType partName;
        char ruleOperator;
        long long threshold;
        RuleEvaluator evaluator;
        std::string bucket;
    };

    struct Ruleset {
        std::string name;
        std::vector<Rule> rules;
        std::string defaultBucket;
    };

    using RuleMap = std::unordered_map<std::string, Ruleset>;

    // part 1
    size_t getSplitIndex(const std::vector<std::string>& input);
    Rule generateRule(const std::string& rule);
    RuleMap parseRules(const std::vector<std::string>& input);
    std::vector<Part> parseParts(const std::vector<std::string>& input);
    std::vector<Part> processParts(
        const RuleMap& rules,
        const std::vector<Part>& parts
    );
    int accumulatePartValues(const std::vector<Part>& parts);

    // part 2
    struct PartRange {
        Part lower{{
            {X, 1},
            {M, 1},
            {A, 1},
            {S, 1},
        }};
        Part upper{{
           {X, 4000},
           {M, 4000},
           {A, 4000},
           {S, 4000},
       }};
    };

    using PartMultiMap = std::unordered_multimap<std::string, PartRange>;
    size_t calculateTotalAcceptedPermutations(
        PartMultiMap& ranges,
        const RuleMap& rules
    );
}

class Day19 : public Day<int, size_t>
{
public:
    virtual ~Day19() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] size_t part2(const std::vector<std::string>&) const override;
};

#endif // DAY_19_H