#ifndef DAY_07_H
#define DAY_07_H

#include "main/solution/day.h"

enum HandType {
    FIVE_OF_A_KIND = 6,
    FOUR_OF_A_KIND = 5,
    FULL_HOUSE = 4,
    THREE_OF_A_KIND = 3,
    TWO_PAIR = 2,
    ONE_PAIR = 1,
    HIGH_CARD = 0
};

enum CardType {
    ACE = 14,
    KING = 13,
    QUEEN = 12,
    JACK = 11,
    TEN = 10,
    NINE = 9,
    EIGHT = 8,
    SEVEN = 7,
    SIX = 6,
    FIVE = 5,
    FOUR = 4,
    THREE = 3,
    TWO = 2,
};

struct Hand {
    std::vector<CardType> cards;
    HandType type;
    int bid;

    Hand(const std::vector<CardType>& cards, HandType type, int bid)
        : cards(cards), type(type), bid(bid)
    {}
};

CardType mapCard(const char& card);
HandType categorizeHand(const std::vector<char>& cards);
std::vector<Hand> parseHands(const std::vector<std::string>& input);

class Day07 : public Day<int>
{
public:
    virtual ~Day07() = default;

    [[nodiscard]] constexpr std::string filename() const override;
    [[nodiscard]] int part1(const std::vector<std::string>&) const override;
    [[nodiscard]] int part2(const std::vector<std::string>&) const override;
};

#endif // DAY_07_H