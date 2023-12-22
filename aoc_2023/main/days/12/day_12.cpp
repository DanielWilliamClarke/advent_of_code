#include "day_12.h"

#include <ranges>
#include <numeric>

#include "main/solution/string_utils.h"

std::vector<SpringManifest> parseRows(const std::vector<std::string>& input, bool unfold)
{
    auto manifests = input
        | std::views::transform([&unfold](const std::string& line) -> SpringManifest {
            auto parts = splitString(line, " ");

            auto springs = parts.front();

            auto manifestView = splitString(parts.back(), ",")
                | std::views::transform([=](const std::string& number) { return std::stoi(number); });

            std::vector<int> manifest = { manifestView.begin(), manifestView.end() };

            if (unfold)
            {
                std::string springFolds;
                std::vector<int> manifestFolds;
                manifestFolds.reserve(manifest.size() * 5);

                // Generate 5 copies of manifest
                for (auto i = 0; i < 5; i++)
                {
                    if (i == 0) {
                        springFolds += springs;
                    } else {
                        springFolds += '?' + springs;
                    }

                    manifestFolds.insert(manifestFolds.end(), manifest.begin(), manifest.end());
                }

                springs = springFolds;
                manifest = manifestFolds;
            }

            return {
                springs,
                manifest
            };
        });

    return { manifests.begin(), manifests.end() };
}

long long processWorkingSpring (
    MemoMap& memo,
    const std::string& springs,
    const std::vector<int>& manifest
)
{
    // simply move to the next spring
    return countPermutations(
        memo,
        { springs.begin() + 1, springs.end() },
        manifest
    );
}

long long processBrokenSpring (
    MemoMap& memo,
    const std::string& springs,
    const std::vector<int>& manifest
)
{
    auto nextGroup = manifest.front();

    // capture the next n springs
    std::string candidateRange = { springs.begin(), springs.begin() + nextGroup };

    // Attempt to generate contiguous group
    auto processedCandidate = candidateRange
        | std::views::transform([=] (const char& spring) {
            return spring == '?' ? '#' : spring;
        });

    std::string candidate = { processedCandidate.begin(), processedCandidate.end()};

    // if group is not contiguous do not count permutation
    if (candidate != std::string(nextGroup, '#'))
    {
        return 0;
    }

    // if we are at the end of the manifest return
    if (springs.size() == nextGroup)
    {
        return manifest.size() == 1
            ? 1
            : 0;
    }

    // if the spring after this contiguous group is not broken
    if (springs[nextGroup] != '#')
    {
        // move to the next spring
        return countPermutations(
            memo,
            { springs.begin() + nextGroup + 1, springs.end() },
            { manifest.begin() + 1, manifest.end() }
        );
    }

    return 0;
}

long long countPermutations(
    MemoMap& memo,
    const std::string& springs,
    const std::vector<int>& manifest
)
{
    // look in memo to reduce workload
    Memo m = std::make_pair(springs.size(), manifest.size());
    if (memo.contains(m))
    {
        return memo[m];
    }

    // if manifest empty we have nothing else to do
    if (manifest.empty())
    {
        return springs.find_first_of('#') == std::string::npos
            ? 1
            : 0;
    }

    // if springs is empty then we cant go further
    if (springs.empty())
    {
        return 0;
    }

    // determine how to process the next spring
    long long out = 0;

    switch (springs.front())
    {
        case '#': {
            out = processBrokenSpring(memo, springs, manifest);
            break;
        }
        case '.': {
            out = processWorkingSpring(memo, springs, manifest);
            break;
        }
        case '?': {
            out = (
                processWorkingSpring(memo, springs, manifest)
                    +
                processBrokenSpring(memo, springs, manifest)
            );
            break;
        }
        default: exit(1);
    };

    memo[m] = out;

    return out;
}

constexpr std::string Day12::filename () const 
{
    return "main/days/12/input.txt";
}

long long sumPermutations(const std::vector<SpringManifest>& manifests)
{
    return std::transform_reduce(
        manifests.begin(),
        manifests.end(),
        0ll,
        std::plus<>(),
        [=] (const SpringManifest& springManifest) {
            MemoMap memo;

            return countPermutations(
                    memo,
                    springManifest.springs,
                    springManifest.manifest
            );
        }
    );
}

long long Day12::part1(const std::vector<std::string>& input) const
{
    return sumPermutations(parseRows(input));
}

long long Day12::part2(const std::vector<std::string>& input) const
{
    return sumPermutations(parseRows(input, true));
}