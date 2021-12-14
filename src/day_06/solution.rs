use std::{cell::{RefCell}, rc::Rc};
use itertools::Itertools;

use crate::common::Solution;

const SPAWN: i32 = 0;
const RESET: i32 = 6;
const FRESH: i32 = 8;

pub struct Day06;

impl Solution<String, i32> for Day06 {
    fn pt_1(&self, input: &[String]) -> i32 {
       self.simulate(&self.parse(input), 80)
    }

    fn pt_2(&self, input: &[String]) -> i32 {
       0
    }
}

impl Day06 {
    pub fn new() -> Day06 {
        Day06 {}
    }

    fn parse(&self, input: &[String]) -> Vec<i32> {
        input
            .first()
            .unwrap()
            .split(',')
            .map(|number| number.parse().unwrap())
            .collect()
    }

    fn simulate(&self, input: &[i32], iterations: usize) -> i32 {
        let mut snapshots = vec![self.create_mut_snapshot(input.to_vec())];
        for _ in 0..iterations {
            snapshots.push(self.create_mut_snapshot(Vec::<i32>::new()));
        }

        snapshots
            .iter()
            .tuple_windows::<(_,_)>()
            .map(|(current, next)| {
                let mut next = next.borrow_mut();
                current
                    .borrow()
                    .iter()
                    .for_each(|timer| {
                        match *timer == SPAWN {
                            true =>  next.append(&mut vec![RESET, FRESH]),
                            false => next.push(timer - 1)
                        }
                    });

                next.len() as i32
            })
            .collect::<Vec<i32>>()
            .last()
            .unwrap_or(&0)
            .to_owned()
    }

    fn create_mut_snapshot(&self, input: Vec<i32>) -> Rc<RefCell<Vec<i32>>>{
        Rc::new(RefCell::new(input))
    }
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_06::solution::Day06};

    #[test]
    fn solution_is_correct() {
        let day = Day06::new();
        let input = day.read_input("src/day_06/input.txt");
        vec![(day.pt_1(&input), 390011)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
