// src/day_04/solution.rs

use crate::common::Solution;

pub struct Day04 {}

impl Solution<String, i32> for Day04 {
    fn pt_1(&self, input: &[String]) -> i32 {
        0
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        0
    }
}

impl Day04 {
    pub fn new() -> Day04 {
        Day04 {}
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
