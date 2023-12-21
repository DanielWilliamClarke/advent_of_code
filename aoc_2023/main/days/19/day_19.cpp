#include "day_19.h"

#include <ranges>
#include <regex>
#include <numeric>

#include "main/solution/string_utils.h"

size_t day19::getSplitIndex(const std::vector<std::string>& input)
{
    for(auto i = 0; i < input.size(); i++)
    {
        if(input[i].empty())
        {
            return i;
        }
    }

    return 0;
}

const std::regex ruleRegex(R"((\w+)\{(.+),(\w+)\})");
const std::regex ruleClauseRegex(R"(([xmas])([><])([0-9]+):(\w+))");

day19::Rule day19::generateRule(const std::string& rule)
{
    std::smatch match;
    std::regex_search(rule, match, ruleClauseRegex);

    auto partName = static_cast<PartType>(match[1].str().front());
    auto ruleOperator = match[2].str().front();
    auto threshold = std::stoi(match[3].str());
    auto bucket = match[4].str();

    auto ruleEvaluator = [partName, ruleOperator, threshold] (const Part& part) -> bool {
        int partValue = part.at(partName);

        switch (ruleOperator)
        {
            case '>': return partValue > threshold;
            case '<': return partValue < threshold;
            default: return false;
        }
    };

    return {
        partName,
        ruleOperator,
        threshold,
        ruleEvaluator,
        bucket
    };
}

day19::RuleMap day19::parseRules(const std::vector<std::string>& input)
{
    std::unordered_map<std::string, day19::Ruleset> rulesMap;

    for (const auto& line : input) {
        std::smatch match;
        std::regex_search(line, match, ruleRegex);

        auto name= match[1].str();
        auto clauses = match[2].str();
        auto defaultBucket= match[3].str();

        auto rules = splitString(clauses, ',')
             | std::views::transform([=](const std::string& rule) {
            return generateRule(rule);
        });

        rulesMap.insert({
            name,
            {
                name,
                { rules.begin(), rules.end() },
                defaultBucket
            }
        });
    }

    return rulesMap;
}

const std::regex partsRegex(R"(\{x=([0-9]+),m=([0-9]+),a=([0-9]+),s=([0-9]+)\})");

std::vector<day19::Part> day19::parseParts(const std::vector<std::string>& input)
{
    auto parts = input
        | std::views::transform([=](const std::string& line) -> Part {
            std::smatch match;
            std::regex_search(line, match, partsRegex);

            return {
                { X, std::stoll(match[1].str()) },
                { M, std::stoll(match[2].str()) },
                { A, std::stoll(match[3].str()) },
                { S, std::stoll(match[4].str()) },
            };
        });

    return { parts.begin(), parts.end() };
}

std::vector<day19::Part> day19::processParts(
    const RuleMap& rules,
    const std::vector<Part>& parts
)
{
    std::vector<day19::Part> acceptedParts;

    for(const auto& part: parts)
    {
        auto rule = rules.at("in");

        while(true)
        {
            for(const auto& clause: rule.rules)
            {
                if (clause.evaluator(part))
                {
                    if (clause.bucket == "A")
                    {
                        acceptedParts.push_back(part);
                        goto nextPart;
                    } 
                    else if (clause.bucket == "R")
                    {
                        // do nothing ignore this part
                        goto nextPart;
                    }

                    rule = rules.at(clause.bucket);
                    goto nextRule;
                }
            }

            // we will get here all rules are not applicable
            // we should then check the default bucket
            if (rule.defaultBucket == "A")
            {
                acceptedParts.push_back(part);
                goto nextPart;
            }
            else if (rule.defaultBucket == "R")
            {
                // do nothing ignore this part
                goto nextPart;
            }

            rule = rules.at(rule.defaultBucket);

            nextRule:
                continue;
        }

        // move to the next part in the list
        nextPart:
            continue;
    }

    return acceptedParts;
}

int day19::accumulatePartValues(const std::vector<Part>& parts)
{
    return std::transform_reduce(
        parts.begin(),
        parts.end(),
        0,
        std::plus<>(),
        [=] (const Part& part) {
            return part.at(X) +
                part.at(M) +
                part.at(A) +
                part.at(S);
        }
    );
}

size_t day19::calculateTotalAcceptedPermutations(
    PartMultiMap& ranges,
    const RuleMap& rules
)
{
    size_t total = 0;
    auto storeRange = [&total, &ranges](const std::string& bucket, const PartRange& range) {
        if (bucket == "A")
        {
            // Calculate permutations that can be accepted
            total += (range.upper.at(X) - range.lower.at(X) + 1) *
                     (range.upper.at(M) - range.lower.at(M) + 1) *
                     (range.upper.at(A) - range.lower.at(A) + 1) *
                     (range.upper.at(S) - range.lower.at(S) + 1);
        }
        else if (bucket != "R")
        {
            ranges.insert({ bucket, range });
        }
    };

    auto rangeIter = ranges.begin();
    auto oldRange = rangeIter->second;
    const auto& rule = rules.at(rangeIter->first);

    // pop first range from the multimap
    ranges.erase(rangeIter);

    for (const auto& clause : rule.rules)
    {
        auto lowerWorks = clause.evaluator(oldRange.lower);
        auto upperWorks = clause.evaluator(oldRange.upper);
        if (!(lowerWorks ^ upperWorks))
        {
            continue;
        }

        // Adjust thresholds based on evaluator result
        auto newRange = oldRange;
        if (lowerWorks && !upperWorks)
        {
            oldRange.lower[clause.partName] = clause.threshold;
            newRange.upper[clause.partName] = clause.threshold - 1;
        }
        else if (upperWorks && !lowerWorks)
        {
            newRange.lower[clause.partName] = clause.threshold + 1;
            oldRange.upper[clause.partName] = clause.threshold;
        }

        // Store new ranges in multimap
        storeRange(clause.bucket, newRange);
    }

    // Store remaining ranges in multimap
    storeRange(rule.defaultBucket, oldRange);

    return total;
}

constexpr std::string Day19::filename () const 
{
    return "main/days/19/input.txt";
}

int Day19::part1(const std::vector<std::string>& input) const
{
    auto splitIndex = day19::getSplitIndex(input);

    return day19::accumulatePartValues(
        day19::processParts(
            day19::parseRules({ input.begin(), input.begin() + splitIndex }),
            day19::parseParts({ input.begin() + splitIndex + 1, input.end() })
        )
    );
}

size_t Day19::part2(const std::vector<std::string>& input) const
{
    auto splitIndex = day19::getSplitIndex(input);
    auto rules = day19::parseRules({ input.begin(), input.begin() + splitIndex });

    size_t permutations = 0;
    day19::PartMultiMap ranges = {{ "in", day19::PartRange{} }};
    while(!ranges.empty())
    {
        permutations += day19::calculateTotalAcceptedPermutations(ranges, rules);
    }

    return permutations;
}