use crate::common::Solution;

pub struct Day07;

impl Solution<String, i32> for Day07 {
    fn pt_1(&self, input: &[String]) -> i32 {
       0
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        0
    }
}

impl Day07 {
    pub fn new() -> Day07 {
        Day07 {}
    }

    fn parse(&self, input: &[String]) -> Vec<i32> {
        input
            .first()
            .unwrap()
            .split(',')
            .map(|number| number.parse().unwrap())
            .collect()
    }

}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_07::solution::Day07};

    #[test]
    fn solution_is_correct() {
        let day = Day07::new();
        let input = day.read_input("src/day_07/input.txt");
        vec![
            (day.pt_1(&input), 0),
            (day.pt_2(&input), 0),
        ]
        .iter()
        .for_each(|test| assert_eq!(test.0, test.1))
    }
}
