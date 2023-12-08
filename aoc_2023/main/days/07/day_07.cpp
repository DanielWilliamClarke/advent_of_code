#include "day_07.h"

#include <ranges>
#include <numeric>
#include <algorithm>

#include "main/solution/string_utils.h"

CardType mapCard(const char& card, bool jokersWild)
{
    switch (card)
    {
        case 'A': return CardType::ACE;
        case 'K': return CardType::KING;
        case 'Q': return CardType::QUEEN;
        case 'J': return jokersWild ? CardType::JOKER : CardType::JACK;
        case 'T': return CardType::TEN;
        default:
            return static_cast<CardType>(card - 0x30);
    }
}

std::pair<HandType, CardType> categorizeHand(const std::vector<Card>& cards)
{
    std::unordered_map<CardType, int> count;
    for(auto card : cards) {
        if(count.contains(card.actingAs)) {
            count[card.actingAs] += 1;
        } else {
            count.insert({ card.actingAs, 1 });
        }
    }

    if (count.size() == 1) {
        return { HandType::FIVE_OF_A_KIND, count.begin()->first };
    }

    auto fourOfAKind = std::ranges::find_if(count, [=](std::pair<CardType, int> c) {
        return c.second == 4 && c.first != CardType::JOKER;
    });
    if (fourOfAKind != count.end()) {
        return {
            HandType::FOUR_OF_A_KIND,
            fourOfAKind->first
        };
    }

    auto threeOfAKind = std::ranges::find_if(count, [=](std::pair<CardType, int> c) {
        return c.second == 3 && c.first != CardType::JOKER;
    });
    if (count.size() == 2 && threeOfAKind != count.end()) {
        return {
            HandType::FULL_HOUSE,
            threeOfAKind->first
        };
    }

    if (count.size() == 3 && threeOfAKind != count.end()) {
        return {
            HandType::THREE_OF_A_KIND,
            threeOfAKind->first
        };
    }

    auto twoPairs = std::views::filter(count, [=](std::pair<CardType, int> c) {
        return c.second == 2;
    });
    if (std::ranges::distance(twoPairs) == 2) {
        auto strongest = std::ranges::max_element(
            twoPairs,
            [=](auto a, auto b) -> bool {
                return a.first < b.first;
            });

        return {
            HandType::TWO_PAIR,
            (*strongest).first
        };
    }

    auto pairNotJoker = std::ranges::find_if(count, [=](std::pair<CardType, int> c) {
        return c.second == 2 && c.first != CardType::JOKER;
    });
    if (pairNotJoker != count.end()) {
        return {
            HandType::ONE_PAIR,
            pairNotJoker->first
        };
    }

    auto strongest = std::ranges::max_element(
        count,
        [=](auto a, auto b) -> bool {
            return a.first < b.first;
        });

    return {
        HandType::HIGH_CARD,
        (*strongest).first
    };
}

std::vector<Hand> parseHands(const std::vector<std::string>& input, bool jokersWild)
{
    auto hands = input
        | std::views::transform([&jokersWild](const std::string& line) -> Hand {
            auto parts = splitString(line, ' ');

            auto mappedCards = parts.front()
                | std::views::transform([&jokersWild](const char& card) -> Card {
                    auto cardType = mapCard(card, jokersWild);

                    return { cardType };
                });

            std::vector<Card> cards = { mappedCards.begin(), mappedCards.end() };

            if (jokersWild)
            {
                auto type = categorizeHand(cards);

                auto jokeredCards = cards
                    | std::views::transform([&type](Card card) -> Card {
                        if (card.card == CardType::JOKER) {
                            card.setActingAs(type.second);
                        }

                        return card;
                    });

                cards = { jokeredCards.begin(), jokeredCards.end() };
            }

            auto type = categorizeHand(cards);

            auto bid = std::stoi(parts.back());

            if (type.second == CardType::JOKER) {
                std::cout << "JOKER DETECTED: " << parts.front() << std::endl;
            }

            return { parts.front(), cards, type.first, bid };
        });

    return { hands.begin(), hands.end() };
}

int rankHands(std::vector<Hand> hands)
{
    std::ranges::sort(hands, [=](auto a, auto b) {
        if (a.type == b.type)
        {
            for(auto i = 0; i < b.cards.size(); i++)
            {
                if (a.cards[i].card == b.cards[i].card) {
                    continue;
                }

                return a.cards[i].card < b.cards[i].card;
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

constexpr std::string Day07::filename () const 
{
    return "main/days/07/input.txt";
}

int Day07::part1(const std::vector<std::string>& input) const
{
    auto hands = parseHands(input);

    return rankHands(hands);
}

int Day07::part2(const std::vector<std::string>& input) const 
{
    auto JOKARS_BE_WILD = true;

    auto hands = parseHands(input, JOKARS_BE_WILD);

    return rankHands(hands);
}