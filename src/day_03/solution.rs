// src/day_03/solution.rs

use crate::common::Solution;
use itertools::Itertools;

pub struct Day03 {}

impl Solution<String, i32> for Day03 {
    fn pt_1(&self, input: &[String]) -> i32 {
        let value = self.render(input);
        value * (value ^ 0xFFF)
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        self.calculate(input, false) * self.calculate(input, true)
    }
}

impl Day03 {
    pub fn new() -> Day03 {
        Day03 {}
    }

    fn render(&self, input: &[String]) -> i32 {
        self.to_decimal(
        &input.get(0)
                .unwrap()
                .chars()
                .enumerate()
                .map(|(index, _)| self.popular(&self.transpose(input, index), false))
                .join(""))
    }

    fn calculate(&self, input: &[String], inverse: bool) -> i32 {
        input.get(0)
            .unwrap()
            .chars()
            .enumerate()
            .fold(input.to_owned(), |acc, (index, _)| {
                if acc.len() == 1 {
                    return acc;
                }

                let popular = self.popular(&self.transpose(&acc, index), inverse);
                acc.iter()
                    .filter(|byte| self.string_at_to_i32(byte, index) == popular)
                    .cloned()
                    .collect::<Vec<String>>()
            })
            .iter()
            .map(|byte| self.to_decimal(byte))
            .sum::<i32>()
    }

    fn to_decimal(&self, input: &str) -> i32 {
        i32::from_str_radix(input, 2).unwrap()
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

    fn transpose (&self, input: &[String], index: usize) -> Vec<i32> {
        input
            .iter()
            .map(|inner| self.string_at_to_i32(inner, index))
            .collect::<Vec<i32>>()
    }   

    fn popular(&self, input: &[i32], inverse: bool) -> i32 {
        let average = input.iter().sum::<i32>() as f32 / input.len() as f32;
        if (average >= 0.5) ^ inverse {
            1
        } else {
            0
        }
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
