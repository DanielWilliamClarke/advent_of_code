use std::{cell::RefCell, rc::Rc};

// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

struct Monkey {
    items: Vec<isize>,
    inspections: usize,
    worrier: Box<dyn Fn(&isize) -> isize>,
    test: isize,
    brothers: (usize, usize),
}

impl Monkey {
    fn new(
        items: Vec<isize>,
        worrier: Box<dyn Fn(&isize) -> isize>,
        test: isize,
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

    fn turn(&mut self, brothers: &[Rc<RefCell<Monkey>>]) {
        self.inspections += self.items.drain(..).map(|item| {
            let item = (self.worrier)(&item) / 3;
            let brother = if item % self.test == 0 {
                self.brothers.0
            } else {
                self.brothers.1
            };

            brothers[brother].borrow_mut().items.push(item)
        })
        .count()
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
        self.play::<20>(&mut self.parse(input))
    }

    fn pt_2(&self, _: &[Self::Input]) -> Self::Output2 {
        0
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

    fn parse_items(&self, line: &String) -> Vec<isize> {
        line.split(":")
            .last()
            .unwrap()
            .split(",")
            .map(|item| {
                item.trim().parse::<isize>().unwrap()
            })
            .collect()
    }

    fn parse_worrier(&self, line: &String) -> Box<dyn Fn(&isize) -> isize> {
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
        let value = equation[2].trim().parse::<isize>().unwrap_or(0);

        match operator {
            "+" => Box::new(move |item| item + value),
            "*" if old == "old" => Box::new(move |item| item * item),
            "*" => Box::new(move |item| item * value),
            _ => panic!("unknown operation"),
        }
    }

    fn parse_test(&self, line: &String) -> isize {
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

    fn play<const ROUNDS: usize>(&self, monkeys: &mut [Rc<RefCell<Monkey>>]) -> usize {
        (0..ROUNDS).for_each(|_| {
            monkeys
                .iter()
                .for_each(|monkey| {
                    monkey.borrow_mut().turn(monkeys)
                });
        });

        monkeys
            .sort_by(|a, b| {
                b.borrow().inspections.cmp(&a.borrow().inspections)
            });

        monkeys[0].borrow().inspections * monkeys[1].borrow().inspections
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day11};

    #[test]
    fn solution_is_correct() {
        Day11 {}.validate(0, 0);
    }
}
