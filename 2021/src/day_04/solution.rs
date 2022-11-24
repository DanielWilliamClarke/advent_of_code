// src/day_04/solution.rs

use std::{cell::RefCell, collections::hash_map::Entry::Vacant, collections::HashMap, rc::Rc};
use itertools::Itertools;
use crate::common::Solution;

#[derive(Copy, Clone, Debug)]
struct Element {
    pub number: i32,
    pub called: bool,
}

impl Element {
    fn new(number: i32) -> Element {
        Element {
            number,
            called: false,
        }
    }

    fn call(&mut self) {
        self.called = true;
    }
}

type Numbers = Vec<i32>;
type RcElement = Rc<RefCell<Element>>;
type Line = Vec<RcElement>;
type LineRef<'a> = &'a [RcElement];
type Board = Vec<Line>;
type BoardRef<'a> = &'a [Line];
type Card = Vec<Board>;
type CardRef<'a> = &'a [Board];
type EnumeratedCard = Vec<(usize, Board)>;
type Bingo = (Numbers, Card);

pub struct Day04 {}

impl Solution<String, i32> for Day04 {
    fn pt_1(&self, input: &[String]) -> i32 {
        self.play(self.parse(input))
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        self.play_to_lose(self.parse(input))
    }
}

impl Day04 {
    pub fn new() -> Day04 {
        Day04 {}
    }

    fn parse(&self, input: &[String]) -> Bingo {
        (
            self.parse_numbers(input.get(0).unwrap()),
            self.parse_boards(&input.iter().skip(1).cloned().collect::<Vec<String>>()),
        )
    }

    fn parse_numbers(&self, input: &str) -> Numbers {
        input
            .split(',')
            .map(|number| self.string_to_i32(number))
            .collect::<Numbers>()
    }

    fn parse_boards(&self, input: &[String]) -> Card {
        input
            .iter()
            .filter(|line| !line.is_empty())
            .chunks(5)
            .into_iter()
            .map(|board| {
                board
                    .map(|line| {
                        line.split_whitespace()
                            .map(|number| {
                                Rc::new(RefCell::new(Element::new(self.string_to_i32(number))))
                            })
                            .collect::<Line>()
                    })
                    .collect::<Board>()
            })
            .collect::<Card>()
    }

    fn string_to_i32(&self, input: &str) -> i32 {
        input.to_string().parse::<i32>().unwrap()
    }

    fn play(&self, (numbers, card): Bingo) -> i32 {
        let winner = numbers.iter().find_map(|number| {
            self.call_number(number, &card)
                .first()
                .map(|(_, winner)| (winner.clone(), number))
        });

        match winner {
            Some((board, number)) => self.count_unmarked(&board) * number,
            None => 0,
        }
    }

    fn play_to_lose(&self, (numbers, card): Bingo) -> i32 {
        let mut winners = HashMap::new();
        let mut last_index = usize::MAX;

        numbers.iter().for_each(|n| {
            card.iter().enumerate().for_each(|(index, b)| {
                if let Vacant(e) = winners.entry(index) {
                    self.mark_board(n, b);
                    if self.is_winning_board(b) {
                        e.insert(self.count_unmarked(b) * n);
                    }
                    last_index = index;
                }
            });
        });

        *winners.get(&last_index).unwrap_or(&0)
    }

    fn call_number<'a>(&self, number: &'a i32, card: CardRef<'a>) -> EnumeratedCard {
        card.iter()
            .inspect(|b| self.mark_board(number, b))
            .enumerate()
            .filter(|(_, b)| self.is_winning_board(b))
            .map(|(index, board)| (index, board.clone()))
            .collect::<EnumeratedCard>()
    }

    fn mark_board(&self, number: &i32, board: BoardRef) {
        board
            .iter()
            .flatten()
            .filter(|element| element.as_ref().borrow().number == *number)
            .for_each(|element| element.as_ref().borrow_mut().call());
    }

    fn is_winning_board(&self, board: BoardRef) -> bool {
        // check lines
        let winner = board.iter().any(|line| self.is_row(line));

        // check columns
        winner
            || board
                .get(0)
                .unwrap()
                .iter()
                .enumerate()
                .any(|(index, _)| self.is_column(index, board))
    }

    fn is_row(&self, line: LineRef) -> bool {
        line.iter().all(|element| element.as_ref().borrow().called)
    }

    fn is_column(&self, index: usize, board: BoardRef) -> bool {
        self.is_row(&self.col_to_row(index, board))
    }

    fn col_to_row(&self, index: usize, board: BoardRef) -> Line {
        board
            .iter()
            .map(|line| line.get(index).unwrap().clone())
            .collect::<Line>()
    }

    fn count_unmarked(&self, board: BoardRef) -> i32 {
        board
            .iter()
            .flatten()
            .filter(|element| !element.as_ref().borrow().called)
            .map(|element| element.as_ref().borrow().number)
            .sum::<i32>()
    }
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_04::solution::Day04};

    #[test]
    fn solution_is_correct() {
        let day04 = Day04::new();
        let input = day04.read_input("src/day_04/input.txt");
        vec![(day04.pt_1(&input), 35670), (day04.pt_2(&input), 22704)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
