use crate::common::Solution;

pub struct Day07;

impl Solution<String, u32> for Day07 {
    fn pt_1(&self, input: &[String]) -> u32 {
        self.optimize(
            &self.parse(input),
        |n| n)
    }

    fn pt_2(&self, input: &[String]) -> u32 {
        self.optimize(
            &self.parse(input),
            |n| n * (n + 1) / 2)
    }
}

impl Day07 {
    pub fn new() -> Day07 {
        Day07 {}
    }

    fn parse(&self, input: &[String]) -> Vec<u32> {
        input
            .first()
            .unwrap()
            .split(',')
            .map(|number| number.parse().unwrap())
            .collect()
    }

    fn optimize (&self, input: &[u32], cost_predicate: fn(u32) -> u32) -> u32 {
        let max = input.iter().max().unwrap();
        let min = input.iter().min().unwrap();

        (*min..*max)
            .map(|index| {
                input
                    .iter()
                    .map(|position|
                        cost_predicate(index.abs_diff(*position)))
                    .sum::<u32>()
            })
            .min()
            .unwrap()
    }
}

#[cfg(test)]
mod tests {
    use criterion::{criterion_group, criterion_main, Criterion};
    use crate::{common::Solution, day_07::solution::Day07};

    #[test]
    fn solution_is_correct() {
        let day = Day07::new();
        let input = day.read_input("src/day_07/input.txt");
        vec![
            (day.pt_1(&input), 347449),
            (day.pt_2(&input), 98039527),
        ]
        .iter()
        .for_each(|test| assert_eq!(test.0, test.1))
    }
}
