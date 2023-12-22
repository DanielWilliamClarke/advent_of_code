#include "day_20.h"

#include <regex>
#include <ranges>

#include "main/solution/string_utils.h"

void day20::printPulse(const std::string& sender, const std::string& destination, bool pulse)
{
    std::cout << sender << " -" << (pulse ? "high" : "low") << "-> " << destination << std::endl;
}

// Module
day20::Module::Module(
    std::string name,
    std::vector<std::string> destinationNames
)
: name(name),
destinationNames(destinationNames),
destinations({}),
pulse(false)
{}

void day20::Module::findDestination (const ModuleMap& moduleMap)
{
    for (auto& tag : this->destinationNames)
    {
        if (moduleMap.contains(tag))
        {
            this->destinations.push_back(moduleMap.at(tag));
        }
        else
        {
            this->destinations.push_back(
                std::make_shared<Unnamed>(
                        Unnamed(tag)
                )
            );
        }
    }
}

// Unnamed
day20::Unnamed::Unnamed(std::string name)
    : Module(name, {})
{}

void day20::Unnamed::receivePulse(const std::string &sender, bool pulse)
{
    this->pulse = pulse;
}

day20::ModulePair day20::Unnamed::sendPulse()
{
    return { this->pulse, {} };
};

// Broadcaster
day20::Broadcaster::Broadcaster(std::string name, std::vector<std::string> destinationNames)
    : Module(name, destinationNames)
{}

void day20::Broadcaster::receivePulse(const std::string& sender, bool pulse)
{
    // There is a single broadcast module (named broadcaster).
    // When it receives a pulse,
    // it sends the same pulse to all of its destination modules.
    printPulse(sender, this->name, pulse);

    this->pulse = pulse;
}

day20::ModulePair day20::Broadcaster::sendPulse()
{
    for(const auto& d : destinations)
    {
        printPulse(this->name, d->name, pulse);
        d->receivePulse(this->name, this->pulse);
    }

    return { this->pulse, this->destinations };
}

// FlipFlop
day20::FlipFlop::FlipFlop(std::string name, std::vector<std::string> destinationNames)
    : Module(name, destinationNames), enabled(false), shouldIgnore(false)
{}

void day20::FlipFlop::receivePulse(const std::string& sender, bool pulse)
{
    //    Flip-flop modules (prefix %) are either on or off;
    //    they are initially off. If a flip-flop module receives a high pulse,
    //    it is ignored and nothing happens. However,
    //    if a flip-flop module receives a low pulse,
    //    it flips between on and off. If it was off,
    //    it turns on and sends a high pulse.
    //    If it was on, it turns off and sends a low pulse.

    if (pulse)
    {
        this->shouldIgnore = true;
        return;
    }

    this->shouldIgnore = false;
    this->pulse = !this->enabled;
    this->enabled = !this->enabled;
}

day20::ModulePair day20::FlipFlop::sendPulse()
{
    if (!this->shouldIgnore || this->enabled)
    {
        for(const auto& d : destinations)
        {
            printPulse(this->name, d->name, pulse);
            d->receivePulse(this->name, this->pulse);
        }

        return { this->pulse, this->destinations };
    }

    return { this->pulse, {} };
}

// Conjunction
day20::Conjunction::Conjunction(std::string name, std::vector<std::string> destinationNames)
    : Module(name, destinationNames), inputs({})
{}

void day20::Conjunction::receivePulse(const std::string &sender, bool pulse)
{
    // Conjunction modules (prefix &)
    // remember the type of the most recent pulse received
    // from each of their connected input modules;
    // they initially default to remembering a low pulse for each input.
    // When a pulse is received, the conjunction module first
    // updates its memory for that input. Then,
    // if it remembers high pulses for all inputs,
    // it sends a low pulse; otherwise, it sends a high pulse.

    this->inputs[sender] = pulse;
}

day20::ModulePair day20::Conjunction::sendPulse()
{
    auto inputPulse = false;

    if (!this->inputs.empty())
    {
        inputPulse = std::ranges::all_of(
            this->inputs,
            [=] (const auto& input) { return input.second; }
        );
    }

    this->pulse = !inputPulse;

    for(const auto& d : destinations)
    {
        printPulse(this->name, d->name, pulse);
        d->receivePulse(this->name, this->pulse);
    }

    return { this->pulse, this->destinations };
}

void day20::Conjunction::findDestination (const ModuleMap& moduleMap)
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
                moduleMap.insert({moduleName, broadcaster});
                break;
            }
            case '%': {
                auto flipFlip = std::make_shared<FlipFlop>(
                   FlipFlop(name, tags)
                );
                moduleMap.insert({name, flipFlip});
                break;
            }
            case '&': {
                auto conjunction = std::make_shared<Conjunction>(
                    Conjunction(name, tags)
                );
                moduleMap.insert({name, conjunction});
                break;
            }
            // cant happen
            default: exit(1);
        }
    }

    return moduleMap;
}

day20::ModuleMap day20::connectModules(const day20::ModuleMap& moduleMap)
{
    for (auto& module : moduleMap)
    {
        module.second->findDestination(moduleMap);
    }

    return moduleMap;
}

// Module processing
std::pair<int, int> day20::processModule(const std::shared_ptr<Module>& module, std::pair<int, int> count)
{
    auto [pulse, nextModules] = module->sendPulse();

    if (pulse)
    {
        count.first += 1;
    }
    else
    {
        count.second += 1;
    }

    for (const auto& m : nextModules)
    {
        count = processModule(m, count);
    }

    return count;
}

std::pair<int, int> day20::smackButton(const ModuleMap& moduleMap, std::pair<int, int> count)
{
    // Trigger broadcaster first
    auto broadcaster = moduleMap.at("broadcaster");
    broadcaster->receivePulse("button", false);
    auto [pulse, nextModules] = broadcaster->sendPulse();

    // update low pulses
    count.second += broadcaster->destinations.size();

    // process all modules
    count = processModule(
        nextModules.front(),
        count
    );

    return count;
}

constexpr std::string Day20::filename () const
{
    return "main/days/20/example2.txt";
}

int Day20::part1(const std::vector<std::string>& input) const
{
    auto modules = day20::connectModules(day20::parseModules(input));

    std::pair<int, int> count = { 0, 0 };
    for (auto i = 0; i < 1; i++)
    {
        count = smackButton(modules, count);
    }

    return count.first * count.second;
}

int Day20::part2(const std::vector<std::string>& input) const
{
    return 0;
}