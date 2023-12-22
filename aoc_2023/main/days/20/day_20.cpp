#include "day_20.h"

#include <regex>
#include <queue>
#include <ranges>

#include "main/solution/string_utils.h"

void day20::printPulse(const std::string& sender, const std::string& destination, bool pulse)
{
    std::cout << sender << " -" << (pulse ? "high" : "low") << "-> " << destination << std::endl;
}

// Module
day20::Module::Module(std::string name, std::vector<std::string> destinationNames)
    : name(name), destinationNames(destinationNames), destinations({}), pulse(false)
{}

void day20::Module::findDestination (ModuleMap& moduleMap)
{
    for (auto& tag : this->destinationNames)
    {
        if (moduleMap.contains(tag))
        {
            this->destinations.push_back(moduleMap.at(tag));
        }
        else
        {
            // handle the fact that there can be modules not mentioned in the main list
            auto unnamed = std::make_shared<Unnamed>(Unnamed(tag));
            this->destinations.push_back(unnamed);
            moduleMap.insert({tag, unnamed});
        }
    }
}

// Unnamed
day20::Unnamed::Unnamed(std::string name)
    : Module(name, {})
{}

day20::SignalList day20::Unnamed::receive(const day20::Signal& signal)
{
    return {};
};

// Broadcaster
day20::Broadcaster::Broadcaster(std::string name, std::vector<std::string> destinationNames)
    : Module(name, destinationNames)
{}

day20::SignalList day20::Broadcaster::receive(const day20::Signal& signal)
{
    // There is a single broadcast module (named broadcaster).
    // When it receives a pulse,
    // it sends the same pulse to all of its destination modules.
    this->pulse = signal.pulse;

    auto signals = this->destinations
        | std::views::transform([&] (const auto& d) -> Signal {
            return { this->name, d->name, this->pulse };
        });

    return { signals.begin(), signals.end() };
}

// FlipFlop
day20::FlipFlop::FlipFlop(std::string name, std::vector<std::string> destinationNames)
    : Module(name, destinationNames), enabled(false), shouldIgnore(false)
{}

day20::SignalList day20::FlipFlop::receive(const day20::Signal &signal)
{
    //    Flip-flop modules (prefix %) are either on or off;
    //    they are initially off. If a flip-flop module receives a high pulse,
    //    it is ignored and nothing happens. However,
    //    if a flip-flop module receives a low pulse,
    //    it flips between on and off. If it was off,
    //    it turns on and sends a high pulse.
    //    If it was on, it turns off and sends a low pulse.
    if (signal.pulse)
    {
        return {};
    }

    this->enabled = !this->enabled;
    this->pulse = this->enabled;

    auto signals = this->destinations
       | std::views::transform([&] (const auto& d) -> Signal {
            return { this->name, d->name, this->pulse };
        });

    return { signals.begin(), signals.end() };
}

// Conjunction
day20::Conjunction::Conjunction(std::string name, std::vector<std::string> destinationNames)
    : Module(name, destinationNames), inputs({})
{}

day20::SignalList day20::Conjunction::receive(const day20::Signal &signal)
{
    // Conjunction modules (prefix &)
    // remember the type of the most recent pulse received
    // from each of their connected input modules;
    // they initially default to remembering a low pulse for each input.
    // When a pulse is received, the conjunction module first
    // updates its memory for that input. Then,
    // if it remembers high pulses for all inputs,
    // it sends a low pulse; otherwise, it sends a high pulse.
    this->inputs[signal.name] = signal.pulse;

    this->pulse = !std::ranges::all_of(
        this->inputs,
        [=] (const auto& input) { return input.second; }
    );

    auto signals = this->destinations
       | std::views::transform([&] (const auto& d) -> Signal {
            return { this->name, d->name, this->pulse };
        });

    return { signals.begin(), signals.end() };
}

void day20::Conjunction::findDestination(ModuleMap& moduleMap)
{
    Module::findDestination(moduleMap);

    // fill input map
    for(const auto& module : moduleMap)
    {
        for (const auto& tag : module.second->destinationNames)
        {
            if (this->name == tag)
            {
                // add to the input map
                this->inputs.insert({ module.second->name, false });
            }
        }
    }
}

// Parse input
const std::regex moduleRegex(R"(([&%b])(\w+) -> ([\w, ]+))");

day20::ModuleMap day20::parseModules(const std::vector<std::string>& input)
{
    ModuleMap moduleMap;

    for(const auto& line : input)
    {
        std::smatch match;
        std::regex_search(line, match, moduleRegex);

        auto type = match[1].str().front();
        auto name = match[2].str();
        auto tags = splitString(match[3].str(), ", ");

        switch (type)
        {
            case 'b': {
                auto moduleName = type + name;
                auto broadcaster = std::make_shared<Broadcaster>(
                    Broadcaster(moduleName,tags )
                );
                moduleMap.insert({ moduleName, broadcaster });
                break;
            }
            case '%': {
                auto flipFlip = std::make_shared<FlipFlop>(
                   FlipFlop(name, tags)
                );
                moduleMap.insert({ name, flipFlip });
                break;
            }
            case '&': {
                auto conjunction = std::make_shared<Conjunction>(
                    Conjunction(name, tags)
                );
                moduleMap.insert({ name, conjunction });
                break;
            }
            // cant happen
            default: exit(1);
        }
    }

    return moduleMap;
}

day20::ModuleMap day20::connectModules(ModuleMap& moduleMap)
{
    for (auto& module : moduleMap)
    {
        module.second->findDestination(moduleMap);
    }

    return moduleMap;
}

day20::PulseCount day20::smackButton(const ModuleMap& moduleMap, PulseCount& count)
{
    std::queue<Signal> processQueue;
    processQueue.push({
        "button",
        "broadcaster",
        false
    });

    while (!processQueue.empty())
    {
        auto currentSignal = processQueue.front();
        processQueue.pop();

        printPulse(currentSignal.name, currentSignal.destination, currentSignal.pulse);

        // increment count
        currentSignal.pulse
            ? count.first += 1
            : count.second += 1;

        auto signals = moduleMap
            .at(currentSignal.destination)
            ->receive(currentSignal);

        for (const auto& s : signals)
        {
            processQueue.push(s);
        }
    }

    return count;
}

constexpr std::string Day20::filename () const
{
    return "main/days/20/input.txt";
}

size_t Day20::part1(const std::vector<std::string>& input) const
{
    auto modules = day20::parseModules(input);
    modules = day20::connectModules(modules);

    day20::PulseCount count = { 0, 0 };
    for (auto i = 0; i < 1000; i++)
    {
        std::cout << "Button smack: " << (i + 1) << " ---------" << std::endl;
        count = smackButton(modules, count);
    }

    return count.first * count.second;
}

size_t Day20::part2(const std::vector<std::string>& input) const
{
    return 0;
}