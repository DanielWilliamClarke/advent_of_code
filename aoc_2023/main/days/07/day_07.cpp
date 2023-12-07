#include "day_07.h"

#include <ranges>
#include <numeric>
#include <algorithm>

#include "main/solution/string_utils.h"

CardType mapCard(const char& card)
{
    switch (card)
    {
        case 'A': return CardType::ACE;
        case 'K': return CardType::KING;
        case 'Q': return CardType::QUEEN;
        case 'J': return CardType::JACK;
        case 'T': return CardType::TEN;
        default:
            return static_cast<CardType>(card - 0x30);
    }
}

HandType categorizeHand(const std::vector<CardType>& cards)
{
    std::unordered_map<CardType, int> count;
    for(auto card : cards) {
        if(count.contains(card)) {
            count[card] += 1;
        } else {
            count.insert({ card, 1 });
        }
    }

    if (count.size() == 1) {
        return HandType::FIVE_OF_A_KIND;
    }

    if (
        count.size() == 2 &&
        std::ranges::any_of(count, [=](std::pair<char, int> c) { return c.second == 4; })
    ) {
        return HandType::FOUR_OF_A_KIND;
    }

    if (
        count.size() == 2 &&
        std::ranges::any_of(count, [=](std::pair<char, int> c) { return c.second == 3; })
    ) {
        return HandType::FULL_HOUSE;
    }

    if (
        count.size() == 3 &&
        std::ranges::any_of(count, [=](std::pair<char, int> c) { return c.second == 3; })
    ) {
        return HandType::THREE_OF_A_KIND;
    }

    if (
        count.size() == 3 &&
        std::ranges::count_if(count, [=](std::pair<char, int> c) { return c.second == 2; }) == 2
    ) {
        return HandType::TWO_PAIR;
    }

    if (
        count.size() == 4 &&
        std::ranges::count_if(count, [=](std::pair<char, int> c) { return c.second == 2; }) == 1
    ) {
        return HandType::ONE_PAIR;
    }

    return HandType::HIGH_CARD;
}

std::vector<Hand> parseHands(const std::vector<std::string>& input)
{
    auto hands = input
        | std::views::transform([](const std::string& line) -> Hand {
            auto parts = splitString(line, ' ');

            auto mappedCards = parts.front()
                    | std::views::transform([](const char& card) { return mapCard(card); });

            std::vector<CardType> cards = { mappedCards.begin(), mappedCards.end() };

            auto type = categorizeHand(cards);

            auto bid = std::stoi(parts.back());

            return { cards, type, bid };
        });

    return { hands.begin(), hands.end() };
}

constexpr std::string Day07::filename () const 
{
    return "main/days/07/input.txt";
}

int Day07::part1(const std::vector<std::string>& input) const
{
    auto hands = parseHands(input);

    std::ranges::sort(hands, [=](auto a, auto b) {
        if (a.type == b.type)
        {
            for(auto i = 0; i < b.cards.size(); i++)
            {
                if (a.cards[i] == b.cards[i]) {
                    continue;
                }

                return a.cards[i] < b.cards[i];
            }
        }

        return a.type < b.type;
    });

    auto total = 0;
    for(auto i = 0; i < hands.size(); i++) {
        total += hands.at(i).bid * (i + 1);
    }

    return total;
}

int Day07::part2(const std::vector<std::string>& input) const 
{
    return 0;
}