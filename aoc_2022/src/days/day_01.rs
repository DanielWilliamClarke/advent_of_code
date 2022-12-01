// src/days/day_01.rs

use std::collections::BinaryHeap;
use crate::utils::solution::Solution;

pub struct Day01;

impl Solution for Day01 {
    type Input = String;
    type Output = i32;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_1.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.sum_per_elf(input)
            .iter()
            .max()
            .unwrap()
            .to_owned()
    } 

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        BinaryHeap::from(self.sum_per_elf(input))
            .into_sorted_vec()
            .iter()
            .rev()
            .take(3)
            .sum::<i32>()
    }
}

impl Day01 {
    fn parse_elves(&self, input: &[String]) -> Vec<Vec<i32>> {
        input
            .split(|line| line.is_empty())
            .map(|group| group
                .iter()
                .map(|line| line.to_string().parse::<i32>().unwrap())
                .collect::<Vec<i32>>())
            .collect::<Vec<Vec<i32>>>()
    }

    fn sum_per_elf(&self, input: &[String]) -> Vec<i32> {
        self.parse_elves(&input)
            .iter()
            .map(|list| list.iter().sum::<i32>())
            .collect::<Vec<i32>>()
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day01, utils::validator::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day01{}.validate((72511, 212117));
    }
}
