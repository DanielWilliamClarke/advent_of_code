#ifndef DAY_08_H
#define DAY_08_H

#include <utility>

#include "main/solution/day.h"

enum Direction {
    Right,
    Left
};

struct NodeConfig {
    std::string name;
    std::string leftName;
    std::string rightName;

    NodeConfig(std::string name, std::string leftName, std::string rightName)
        : name(name), leftName(leftName), rightName(rightName)
    {}
};

struct Node {
    NodeConfig config;
    bool isDestination;

    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(NodeConfig config, bool isDestination)
        : config(config), isDestination(isDestination)
    {}

    void setLeft(std::shared_ptr<Node>& l) {
        this->left = l;
    }

    void setRight(std::shared_ptr<Node>& r) {
        this->right = r;
    }
};

std::vector<std::shared_ptr<Node>> parseNodes(const std::vector<std::string>& input);
std::vector<Direction> parseDirections(const std::string& line);
int traverse(std::shared_ptr<Node> node, std::vector<Direction> directions);

class Day08 : public Day<int, unsigned long long>
{
public:
    virtual ~Day08() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] unsigned long long part2(const std::vector<std::string>&) const override;
};

#endif // DAY_08_H