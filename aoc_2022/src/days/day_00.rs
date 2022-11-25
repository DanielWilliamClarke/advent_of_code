// src/days/day_00/solution.rs

use crate::utils::solution::Solution;
#[derive(Copy, Clone)]
pub struct Day00;

impl Solution<i32, usize> for Day00 {
    fn new() -> Self {
        Self {}
    }

    fn pt_1(&self, _: &[i32]) -> usize {
        0
    }

    fn pt_2(&self, _: &[i32]) -> usize {
        0
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::solution::Solution, Day00};

    #[test]
    fn solution_is_correct() {
        let day00 = Day00::new();
        let input = day00.read_input("src/days/input/day_0.txt");
        vec![(day00.pt_1(&input), 0), (day00.pt_2(&input), 0)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
