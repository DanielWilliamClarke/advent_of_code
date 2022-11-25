use crate::solution::Solution;

#[derive(Copy, Clone)]
pub struct Day01;

impl Solution<i64, usize> for Day01 {
    fn new() -> Self {
        Self {}
    }

    fn pt_1(&self, _: &[i64]) -> usize {
        0
    }

    fn pt_2(&self, _: &[i64]) -> usize {
        0
    }
}

#[cfg(test)]
mod tests {
    use crate::{solution::Solution, Day01};

    #[test]
    fn solution_is_correct() {
        let day = Day01::new();
        let input = day.read_input("src/day_01/input.txt");
        vec![(day.pt_1(&input), 0), (day.pt_2(&input), 0)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}