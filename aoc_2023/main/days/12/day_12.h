#ifndef DAY_12_H
#define DAY_12_H

#include "main/solution/day.h"

#include <map>

using Memo = std::pair<int, int>;
using MemoMap = std::map<Memo, long long>;

struct SpringManifest
{
    std::string springs;
    std::vector<int> manifest;

    SpringManifest(std::string springs, std::vector<int> manifest)
        : springs(springs), manifest(manifest)
    {}
};

std::vector<SpringManifest> parseRows(const std::vector<std::string>& input, bool unfold = false);

long long processWorkingSpring (
    MemoMap& memo,
    const std::string& springs,
    const std::vector<int>& manifest
);

long long processBrokenSpring (
    MemoMap& memo,
    const std::string& springs,
    const std::vector<int>& manifest
);

long long countPermutations(
    MemoMap& memo,
    const std::string& springs,
    const std::vector<int>& manifest
);

long long sumPermutations(const std::vector<SpringManifest>& manifests);

class Day12 : public Day<long long>
{
public:
    virtual ~Day12() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] long long part1(const std::vector<std::string>&) const override;
    [[nodiscard]] long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_12_H