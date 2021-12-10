// src/day_04/solution.rs

use std::{cell::RefCell, rc::Rc, borrow::Borrow};

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
type Bingo = (Numbers, Card);

pub struct Day04 {}

impl Solution<String, i32> for Day04 {
    fn pt_1(&self, input: &[String]) -> i32 {
        self.play(self.parse(input))
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        0
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
        numbers
            .iter()
            .find_map(|number| self.call_number(number, &card))
            .unwrap_or(0)
    }

    fn call_number(&self, number: &i32, card: CardRef) -> Option<i32> {
        card
            .iter()
            .find_map(|board| {
               
                let winning = board
                    .iter()
                    .find_map(|line| {
                        line
                            .iter()
                            .enumerate()
                            .find(|(index, element)| {
                                if element.as_ref().borrow().number == *number {
                                    element.borrow_mut().call();
                                    return self.winning_line(line) || self.winning_column(*index, board)
                                }
                                false
                            })
                    });

                winning.map(|_| self.count_unmarked(board) * number)
            })
    }

    fn winning_line(&self, line: LineRef) -> bool {
        line.iter().all(|element| element.as_ref().borrow().called)
    }

    fn winning_column(&self, index: usize, board: BoardRef) -> bool {
        self.winning_line(&self.board_to_line(index, board))
    }

    fn board_to_line(&self, index: usize, board: BoardRef) -> Line {
        board
            .iter()
            .map(|line| line.get(index).unwrap().clone())
            .collect::<Line>()
    }

    fn count_unmarked(&self, board: BoardRef) -> i32 {
        board
            .iter()
            .flatten()
            .inspect(|element| println!("{:?}", element))
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
        vec![(1, 1)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
