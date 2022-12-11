// src/days/day_01.rs

use std::{collections::BinaryHeap, str::FromStr, iter::Sum};
use crate::utils::solution::Solution;
use std::fmt::Debug;

pub struct Day01;

impl Solution for Day01 {
    type Input = String;
    type Output1 = u32;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_1.txt"
    }

    fn pt_1(&self, snacks: &[Self::Input]) -> Self::Output1 {
        self.sum_per_elf(snacks, 1)
    } 

    fn pt_2(&self, snacks: &[Self::Input]) -> Self::Output2 {
        self.sum_per_elf(snacks, 3)
    }
}

impl Day01 {
    fn parse_elf_snacks<T>(&self, snacks: &[String]) -> Vec<Vec<T>>
    where 
        T: FromStr,
        <T as FromStr>::Err: Debug
    {
        snacks
            .split(|snack| snack.is_empty())
            .map(|elf| elf
                .iter()
                .map(|snack| snack.to_string().parse::<T>().unwrap())
                .collect())
            .collect()
    }

    fn sum_per_elf<T>(&self, snacks: &[String], take: usize) -> T
    where 
        T: for<'a> Sum<&'a T> + FromStr + Ord,
        <T as FromStr>::Err: Debug 
    {
        self.parse_elf_snacks(snacks)
            .iter()
            .map(|snack| snack.iter().sum::<T>())
            .rev()
            .collect::<BinaryHeap<T>>()
            .iter()
            .take(take)
            .sum()
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day01, utils::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day01{}.validate(72511, 212117);
    }
}
