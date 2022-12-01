// src/days/day_01.rs
use crate::utils::solution::Solution;

pub struct Day01;

impl Solution for Day01 {
    type Input = String;
    type Output = i32;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_1.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.parse(&input)
            .iter()
            .map(|list| list.iter().sum::<i32>())
            .max()
            .unwrap()
    } 

    fn pt_2(&self, _: &[Self::Input]) -> Self::Output {
        0
    }
}

impl Day01 {
    fn parse(&self, input: &[String]) -> Vec<Vec<i32>> {
        input
            .split(|line| line.is_empty())
            .map(|group| group
                .iter()
                .map(|line| line.to_string().parse::<i32>().unwrap())
                .collect::<Vec<i32>>())
            .collect::<Vec<Vec<i32>>>()
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day01, utils::validator::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day01{}.validate((72511, 0));
    }
}
