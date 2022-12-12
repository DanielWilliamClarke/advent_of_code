use std::{cell::RefCell, collections::VecDeque, rc::Rc};

// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

struct Monkey {
    items: VecDeque<usize>,
    inspections: usize,
    worrier: Box<dyn Fn(&usize) -> usize>,
    test: usize,
    brothers: (usize, usize),
}

impl Monkey {
    fn new(
        items: VecDeque<usize>,
        worrier: Box<dyn Fn(&usize) -> usize>,
        test: usize,
        brothers: (usize, usize),
    ) -> Self {
        Monkey {
            inspections: 0,
            items,
            worrier,
            test,
            brothers,
        }
    }

    fn turn<const RELIEF: usize>(
        &mut self,
        brothers: &[Rc<RefCell<Monkey>>],
        common_divisor: usize,
    ) {
        self.inspections += self
            .items
            .drain(..)
            .map(|item| {
                let item = (self.worrier)(&item) / RELIEF % common_divisor;
                brothers[if item % self.test == 0 {
                    self.brothers.0
                } else {
                    self.brothers.1
                }]
                .borrow_mut()
                .items
                .push_back(item);
            })
            .count() as usize
    }
}

pub struct Day11;

impl Solution for Day11 {
    type Input = String;
    type Output1 = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_11.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output1 {
        self.play::<20, 3>(&mut self.parse(input))
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output2 {
        self.play::<10000, 1>(&mut self.parse(input))
    }
}

impl Day11 {
    fn parse(&self, input: &[String]) -> Vec<Rc<RefCell<Monkey>>> {
        input
            .split(|line| line.is_empty())
            .map(|monkey| self.parse_monkey(monkey))
            .collect()
    }

    fn parse_monkey(&self, input: &[String]) -> Rc<RefCell<Monkey>> {
        Rc::new(RefCell::new(Monkey::new(
            self.parse_items(&input[1]),
            self.parse_worrier(&input[2]),
            self.parse_test(&input[3]),
            self.parse_brothers(&input[4..]),
        )))
    }

    fn parse_items(&self, line: &String) -> VecDeque<usize> {
        line.split(":")
            .last()
            .unwrap()
            .split(",")
            .map(|item| item.trim().parse::<usize>().unwrap())
            .collect()
    }

    fn parse_worrier(&self, line: &String) -> Box<dyn Fn(&usize) -> usize> {
        let equation = line
            .split(":")
            .last()
            .unwrap()
            .split("=")
            .last()
            .unwrap()
            .split_whitespace()
            .collect::<Vec<_>>();

        let operator = equation[1];
        let old = equation[2];
        let value = equation[2].trim().parse::<usize>().unwrap_or(0);

        match operator {
            "+" => Box::new(move |item| (item + value)),
            "*" if old == "old" => Box::new(move |item| (item * item)),
            "*" => Box::new(move |item| (item * value)),
            _ => panic!("unknown operation"),
        }
    }

    fn parse_test(&self, line: &String) -> usize {
        line.split_whitespace().last().unwrap().parse().unwrap()
    }

    fn parse_brothers(&self, lines: &[String]) -> (usize, usize) {
        let brothers = lines
            .iter()
            .map(|line| {
                line.split_whitespace()
                    .last()
                    .unwrap()
                    .parse::<usize>()
                    .unwrap()
            })
            .collect::<Vec<_>>();

        (brothers[0], brothers[1])
    }

    fn play<const ROUNDS: usize, const RELIEF: usize>(
        &self,
        monkeys: &mut [Rc<RefCell<Monkey>>],
    ) -> usize {
        let common_divisor = monkeys.iter().map(|m| m.borrow().test).product();

        (0..ROUNDS).for_each(|_| {
            monkeys
                .iter()
                .for_each(|monkey| monkey.borrow_mut().turn::<RELIEF>(monkeys, common_divisor));
        });

        let mut inspections = monkeys
            .iter()
            .map(|m| m.borrow().inspections)
            .collect::<Vec<_>>();

        inspections.sort();
        inspections.iter().rev().take(2).product()
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day11};

    #[test]
    fn solution_is_correct() {
        Day11 {}.validate(98908, 17673687232);
    }
}
