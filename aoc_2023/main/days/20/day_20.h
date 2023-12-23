#ifndef DAY_20_H
#define DAY_20_H

#include "main/solution/day.h"

namespace day20
{
    void printPulse(const std::string& sender, const std::string& destination, bool pulse);

    struct Module;

    using ModuleMap = std::unordered_map<std::string, std::shared_ptr<Module>>;
    using ModuleList = std::vector<std::shared_ptr<Module>>;
    using PulseCount = std::pair<size_t, size_t>;

    struct Signal
    {
        std::string name;
        std::string destination;
        bool pulse;
    };

    using SignalList = std::vector<Signal>;

    struct Module
    {
        std::string name;
        std::vector<std::string> destinationNames;
        std::vector<std::shared_ptr<Module>> destinations;
        bool pulse;

        Module(
            std::string name,
            std::vector<std::string> destinationNames
        );
        virtual ~Module() = default;

        virtual SignalList receive(const Signal& count) = 0;
        virtual void reset() = 0;
        virtual void findDestination (ModuleMap& moduleMap);
    };

    struct Unnamed : public Module
    {
        Unnamed(std::string name);
        SignalList receive(const Signal& signal) override;
        void reset() override;
    };

    struct Broadcaster : public Module
    {
        Broadcaster(std::string name, std::vector<std::string> destinationNames);
        virtual ~Broadcaster() = default;

        SignalList receive(const Signal& signal) override;
        void reset() override;
    };

    struct FlipFlop : public Module
    {
        bool enabled;
        bool shouldIgnore;

        FlipFlop(std::string name, std::vector<std::string> destinationNames);
        virtual ~FlipFlop() = default;

        SignalList receive(const Signal& signal) override;
        void reset() override;
    };

    struct Conjunction : public Module
    {
        std::unordered_map<std::string, bool> inputs;

        Conjunction(std::string name, std::vector<std::string> destinationNames);
        virtual ~Conjunction() = default;

        SignalList receive(const Signal& signal) override;
        void reset() override;
        void findDestination (ModuleMap& moduleMap) override;
    };

    ModuleMap parseModules(const std::vector<std::string>& input);
    ModuleMap connectModules(ModuleMap& moduleMap);
    PulseCount smackButton(const ModuleMap& moduleMap, PulseCount& count);

    // part 2
    ModuleList findPenultimateModules (const ModuleMap& modules);
    void reinitializeModules(ModuleMap& modules);
    size_t findCycle(ModuleMap& modules, const std::shared_ptr<Module>& from);
}

class Day20 : public Day<size_t>
{
public:
    virtual ~Day20() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] size_t part1(const std::vector<std::string>&) const override;
    [[nodiscard]] size_t part2(const std::vector<std::string>&) const override;
};

#endif // DAY_20_H