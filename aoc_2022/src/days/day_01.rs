// src/days/day_01.rs

use crate::utils::solution::Solution;

#[derive(Copy, Clone)]
pub struct Day01;

impl Solution for Day01 {
    type Input = i64;
    type Output = usize;

    fn pt_1(&self, _: &[i64]) -> usize {
        0
    }

    fn pt_2(&self, _: &[i64]) -> usize {
        0
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::solution::Solution, Day01};

    #[test]
    fn solution_is_correct() {
        let day = Day01 { };
        let input = day.read_input("src/days/input/day_1.txt");
        vec![(day.pt_1(&input), 0), (day.pt_2(&input), 0)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}