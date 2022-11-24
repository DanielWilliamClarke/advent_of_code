// src/day_03/solution.rs

use crate::common::Solution;
use itertools::Itertools;
use std::{iter::Enumerate, str::Chars};

pub struct Day03 {}

impl Solution<String, i32> for Day03 {
    fn pt_1(&self, input: &[String]) -> i32 {
        let value = self.calculate_1(input);
        value * (value ^ 0xFFF)
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        self.calculate_2(input, false) * self.calculate_2(input, true)
    }
}

impl Day03 {
    pub fn new() -> Day03 {
        Day03 {}
    }

    fn calculate_1(&self, input: &[String]) -> i32 {
        self.to_decimal(
        &self.enumerate_bits(input)
                .map(|(index, _)| self.popular(input, index, false))
                .join(""))
    }

    fn calculate_2(&self, input: &[String], inverse: bool) -> i32 {
        self.enumerate_bits(input)
            .fold(input.to_owned(), |acc, (index, _)| {
                if acc.len() == 1 {
                    return acc;
                }

                let popular = self.popular(&acc, index, inverse);
                acc.iter()
                    .filter(|byte| self.string_at_to_i32(byte, index) == popular)
                    .cloned()
                    .collect::<Vec<String>>()
            })
            .iter()
            .map(|byte| self.to_decimal(byte))
            .sum::<i32>()
    }

    fn enumerate_bits<'a>(&self, input: &'a [String]) -> Enumerate<Chars<'a>> {
        input.get(0)
            .unwrap()
            .chars()
            .enumerate()
    }

    fn to_decimal(&self, input: &str) -> i32 {
        i32::from_str_radix(input, 2).unwrap()
    }

    fn popular(&self, input: &[String], index: usize, inverse: bool) -> i32 {
        let average = input
            .iter()
            .map(|inner| self.string_at_to_i32(inner, index))
            .sum::<i32>() as f32 / input.len() as f32;

        if (average >= 0.5) ^ inverse { 1 } else { 0 }
    }

    fn string_at_to_i32(&self, input: &str, index: usize) -> i32 {
        input
            .chars()
            .nth(index)
            .unwrap()
            .to_string()
            .parse::<i32>()
            .unwrap()
    }
 }

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_03::solution::Day03};

    #[test]
    fn solution_is_correct() {
        let day03 = Day03::new();
        let input = day03.read_input("src/day_03/input.txt");
        vec![(day03.pt_1(&input), 1131506), (day03.pt_2(&input), 7863147)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
