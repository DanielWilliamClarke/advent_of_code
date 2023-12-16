#ifndef DAY_16_H
#define DAY_16_H

#include <map>

#include "main/solution/day.h"

enum ContraptionPartType
{
    SPACE = '.',
    MIRROR_RIGHT = '/',
    MIRROR_LEFT = '\\',
    SPLITTER_UP_DOWN = '|',
    SPLITTER_LEFT_RIGHT = '-'
};

struct ContraptionPart
{
    ContraptionPartType type;
    int passes;

    ContraptionPart(ContraptionPartType type)
        : type(type), passes(0)
    {}
};

using StartPosition = std::pair<int, int>;
using RayDirection = std::pair<int, int>;
using Contraption = std::vector<std::vector<std::shared_ptr<ContraptionPart>>>;

bool withinBounds(const Contraption& contraption, const StartPosition& position);
Contraption parseContraption(const std::vector<std::string>& input);
RayDirection mirrorDirection(const RayDirection& direction, ContraptionPartType mirror);
std::vector<RayDirection> splitDirection(const RayDirection& direction, ContraptionPartType splitter);
StartPosition calculateNextPoint(const StartPosition& position, const RayDirection& direction);
void traceContraption(Contraption& contraption, const StartPosition& position, const RayDirection& direction);
int calculateEnergisement(const Contraption& contraption);
Contraption& refreshContraption(Contraption& contraption);

class Day16 : public Day<int>
{
public:
    virtual ~Day16() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_16_H