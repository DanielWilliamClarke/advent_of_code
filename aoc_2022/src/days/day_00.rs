// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

pub struct Day00;

impl Solution for Day00 {
    type Input = i32;
    type Output1 = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_0.txt"
    }

    fn pt_1(&self, _: &[Self::Input]) -> Self::Output1 {
        0
    }

    fn pt_2(&self, _: &[Self::Input]) -> Self::Output2 {
        0
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day00, utils::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day00{}.validate(0, 0);
    }
}
