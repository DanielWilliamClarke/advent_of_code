#ifndef DAY_12_H
#define DAY_12_H

#include "main/solution/day.h"

#include <map>

struct SpringMemoHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};

using Memo = std::pair<int, int>;
using MemoMap = std::unordered_map<Memo, long long, SpringMemoHash>;

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