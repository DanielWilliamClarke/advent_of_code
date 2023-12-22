#ifndef DAY_20_H
#define DAY_20_H

#include "main/solution/day.h"

namespace day20
{
    void printPulse(const std::string& sender, const std::string& destination, bool pulse);

    struct Module;

    using ModuleList = std::vector<std::shared_ptr<Module>>;
    using ModulePair = std::pair<bool, ModuleList>;
    using ModuleMap = std::unordered_map<std::string, std::shared_ptr<Module>>;

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

        virtual void receivePulse(const std::string& sender, bool pulse) = 0;
        virtual ModulePair sendPulse() = 0;

        virtual void findDestination (const ModuleMap& moduleMap);
    };

    struct Unnamed : public Module
    {
        Unnamed(std::string name);
        void receivePulse(const std::string& sender, bool pulse) override;
        ModulePair sendPulse() override;
    };

    struct Broadcaster : public Module
    {
        Broadcaster(std::string name, std::vector<std::string> destinationNames);
        virtual ~Broadcaster() = default;

        void receivePulse(const std::string& sender, bool pulse) override;
        ModulePair sendPulse() override;
    };

    struct FlipFlop : public Module
    {
        bool enabled;
        bool shouldIgnore;

        FlipFlop(std::string name, std::vector<std::string> destinationNames);
        virtual ~FlipFlop() = default;

        void receivePulse(const std::string& sender, bool pulse) override;
        ModulePair sendPulse() override;
    };

    struct Conjunction : public Module
    {
        std::unordered_map<std::string, bool> inputs;

        Conjunction(std::string name, std::vector<std::string> destinationNames);
        virtual ~Conjunction() = default;

        void receivePulse(const std::string& sender, bool pulse) override;
        ModulePair sendPulse() override;

        void findDestination (const ModuleMap& moduleMap) override;
    };



    ModuleMap parseModules(const std::vector<std::string>& input);
    ModuleMap connectModules(const ModuleMap& moduleMap);

    std::pair<int, int> processModule(const std::shared_ptr<Module>& module, std::pair<int, int> count);
    std::pair<int, int> smackButton(const ModuleMap& moduleMap, std::pair<int, int> count);


}

class Day20 : public Day<int>
{
public:
    virtual ~Day20() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_20_H