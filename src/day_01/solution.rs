// src/day_01/solution.rs

use crate::common::Solution;
use itertools::Itertools;
use std::str::FromStr;

pub struct Day01 {}

impl Solution<i32, usize> for Day01 {
    fn pt_1(&self, input: &[i32]) -> usize {
        self.count(input.iter())
    }

    fn pt_2(&self, input: &[i32]) -> usize {
        self.count(
            input
                .iter()
                .tuple_windows::<(_, _, _)>()
                .map(|(a, b, c)| a + b + c),
        )
    }
}

impl Day01 {
    pub fn new() -> Day01 {
        Day01 {}
    }

    fn count<I>(&self, input: I) -> usize
    where
        I: std::iter::Iterator,
        <I as std::iter::Iterator>::Item: std::clone::Clone + std::cmp::PartialOrd,
    {
        input
            .tuple_windows::<(_, _)>()
            .filter(|(a, b)| b > a)
            .count()
    }
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_01::solution::Day01};

    #[test]
    fn solution_is_correct() {
        let day01 = Day01::new();
        let input = day01.read_input("src/day_01/input.txt");
        vec![(day01.pt_1(&input), 1393), (day01.pt_2(&input), 1359)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
