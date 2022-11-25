// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

pub struct Day00;

impl Solution for Day00 {
    type Input = i32;
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
        Day00
    };

    #[test]
    fn solution_is_correct() {
        let day00 = Day00 {};
        let input = day00.read_input("src/days/input/day_0.txt");
        let results = vec![(day00.pt_1(&input), 0), (day00.pt_2(&input), 0)];
        validate_solution(results);
    }
}
