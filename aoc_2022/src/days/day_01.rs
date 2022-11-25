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
        test_utils::validator::validator::validate_solution,
        Day01
    };

    #[test]
    fn solution_is_correct() {
        validate_solution(
            Day01, 
            "src/days/input/day_1.txt", 
            (0, 0)
        );
    }
}
