// src/days/day_01.rs
use crate::utils::solution::Solution;

pub struct Day01;

impl Solution for Day01 {
    type Input = i64;
    type Output = usize;

    fn pt_1(&self, _: &[Self::Input]) -> Self::Output {
        0
    }

    fn pt_2(&self, _: &[Self::Input]) -> Self::Output {
        0
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        utils::{reader::Reader, solution::Solution},
        test_utils::validator::validator::validate_solution,
        Day01
    };

    #[test]
    fn solution_is_correct() {
        let day = Day01 {};
        let input = day.read_input("src/days/input/day_1.txt");
        let results = vec![(day.pt_1(&input), 0), (day.pt_2(&input), 0)];
        validate_solution(results);
    }
}
