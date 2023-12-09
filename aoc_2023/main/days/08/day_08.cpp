#include "day_08.h"

#include <regex>
#include <ranges>
#include <memory>
#include <numeric>

const std::regex regex("(\\w{3}) = \\((\\w{3}), (\\w{3})\\)");

std::vector<std::shared_ptr<Node>> parseNodes(const std::vector<std::string>& input)
{
    // parse each line
   auto nodesViews = input
        | std::views::transform([=](const std::string& line) -> std::shared_ptr<Node> {
            std::smatch match;
            std::regex_search(line, match, regex);
            auto name = match[1].str();
            auto leftName = match[2].str();
            auto rightName =  match[3].str();

            return std::make_shared<Node>(
                Node(
                { name, leftName, rightName },
                name.back() == 'Z'
                )
            );
        });

   // connect up all node pointers
   std::vector<std::shared_ptr<Node>> nodes = { nodesViews.begin(), nodesViews.end() };
   for (const auto& n1: nodes) {
       for(auto n2 : nodes) {
           if (n2->config.name == n1->config.leftName) {
               n1->setLeft(n2);
           }
           if (n2->config.name == n1->config.rightName) {
               n1->setRight(n2);
           }
       }
   }

   return nodes;
}

std::vector<Direction> parseDirections(const std::string& line)
{
    auto directions = line
          | std::views::transform([=](const char& dir) -> Direction {
             switch (dir) {
                 case 'R': return Direction::Right;
                 case 'L': return Direction::Left;
                 default: exit(1);
             }
        });

    return { directions.begin(), directions.end() };
}

int traverse(std::shared_ptr<Node> node, std::vector<Direction> directions)
{
    int step = 0;

    while(!node->isDestination)
    {
        auto instructionIndex = step % directions.size();
        auto direction = directions.at(instructionIndex);

        switch (direction)
        {
            case Direction::Right:
            {
                node = node->right;
                break;
            }
            case Direction::Left:
            {
                node = node->left;
                break;
            }
        }

        step += 1;
    }

    return step;
}

constexpr std::string Day08::filename () const 
{
    return "main/days/08/input.txt";
}

int Day08::part1(const std::vector<std::string>& input) const
{
    auto node = parseNodes({input.begin() + 2, input.end()})
        | std::views::filter([=](const std::shared_ptr<Node>& node) {
            return node->config.name == "AAA";
        });

    return traverse(
        node.front(),
        parseDirections(input.at(0))
    );
}

unsigned long long Day08::part2(const std::vector<std::string>& input) const
{
    auto directions = parseDirections(input.at(0));

    auto pathLengths = parseNodes({input.begin() + 2, input.end()})
        | std::views::filter([=](const std::shared_ptr<Node>& node) {
            return node->config.name.back() == 'A';
        })
        | std::views::transform([&directions](std::shared_ptr<Node>& node) {
            return traverse(node, directions);
        });

    return std::accumulate(
        pathLengths.begin(),
        pathLengths.end(),
        1ull,
        [=](auto a, auto b){
            return std::lcm(a, b);
        });
}