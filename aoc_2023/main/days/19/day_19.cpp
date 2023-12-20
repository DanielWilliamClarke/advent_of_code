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

day19::Rule day19::parseRule(const std::string& rule)
{
    std::smatch match;
    std::regex_search(rule, match, ruleClauseRegex);

    auto partName = match[1].str().front();
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

    return std::make_pair(ruleEvaluator, bucket);
}

std::unordered_map<std::string, day19::Ruleset> day19::parseRules(const std::vector<std::string>& input)
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
            return parseRule(rule);
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
                { 'x', std::stoi(match[1].str()) },
                { 'm', std::stoi(match[2].str()) },
                { 'a', std::stoi(match[3].str()) },
                { 's', std::stoi(match[4].str()) },
            };
        });

    return { parts.begin(), parts.end() };
}

std::vector<day19::Part> day19::processParts(
    const std::unordered_map<std::string, day19::Ruleset>& rules,
    const std::vector<Part>& parts
)
{
    std::vector<day19::Part> acceptedParts;

    for(const auto& part: parts)
    {
        auto rule = rules.at("in");

        while(true)
        {
            for(auto [evaluator, bucket] : rule.rules)
            {
                if (evaluator(part))
                {
                    if (bucket == "A")
                    {
                        acceptedParts.push_back(part);
                        goto nextPart;
                    } 
                    else if (bucket == "R")
                    {
                        // do nothing ignore this part
                        goto nextPart;
                    }

                    rule = rules.at(bucket);
                    goto nextRule;
                }
            }

            // we will get here if no rules are
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
            else
            {
                rule = rules.at(rule.defaultBucket);
            }

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
            return part.at('x') +
                part.at('m') +
                part.at('a') +
                part.at('s');
        }
    );
}

constexpr std::string Day19::filename () const 
{
    return "main/days/19/input.txt";
}

int Day19::part1(const std::vector<std::string>& input) const
{
    auto splitIndex = day19::getSplitIndex(input);

    auto rules = day19::parseRules({ input.begin(), input.begin() + splitIndex });

    auto parts = day19::parseParts({ input.begin() + splitIndex + 1, input.end() });

    auto acceptedParts = day19::processParts(rules, parts);

    return day19::accumulatePartValues(acceptedParts);
}

int Day19::part2(const std::vector<std::string>& input) const 
{
    return 0;
}