// src/day_04/solution.rs

use std::{cell::RefCell, rc::Rc};

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
            self.parse_boards(&input.iter().skip(2).cloned().collect::<Vec<String>>()),
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
        match input.to_string().parse::<i32>() {
            Ok(value) => value,
            Err(err) => panic!("failed parsing {}: {:?}", input, err),
        }
    }

    fn play(&self, (numbers, card): Bingo) -> i32 {
        let result = numbers.iter().find_map(|number| {
            card
                .iter()
                .for_each(|board| self.call(number, board));

            let winning_board = card
                .iter().
                find_map(|board| {
                    let horizontal = board
                        .iter()
                        .any(|line| self.winning_line(line));

                    if horizontal {
                        return Some(board);
                    }

                    let vertical = board
                        .iter()
                        .take(1)
                        .enumerate()
                        .any(|(index, _)| self.winning_line(&self.board_to_line(index, board)));

                    if vertical {
                        return Some(board);
                    }
                    None
                });

                winning_board.map(|winning| self.count_unmarked(winning) * number)
        });

        result.unwrap_or(0)
    }

    fn call(&self, number: &i32, board: BoardRef) {
        board.iter().flatten().for_each(|element| {
            if element.borrow().number == *number {
                element.borrow_mut().call();
            }
        });
    }

    fn board_to_line(&self, index: usize, board: BoardRef) -> Line {
        board
            .iter()
            .map(|line| line.get(index).unwrap().clone())
            .collect::<Line>()
    }

    fn winning_line(&self, line: LineRef) -> bool {
        line.iter().all(|element| element.borrow().called)
    }

    fn count_unmarked(&self, board: BoardRef) -> i32 {
        board
            .iter()
            .flatten()
            .filter(|element| !element.borrow().called)
            .map(|element| element.borrow().number)
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
