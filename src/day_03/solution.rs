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

    fn calculate(&self, input: &[String], inverse: bool) -> i32 {
        (0..input[0].len())
            .fold(self.input_to_bits(input), |acc, index| {
                if acc.len() == 1 {
                    return acc;
                }

                let popular = self.popular(
                    &acc.iter().map(|byte| byte[index]).collect::<Vec<i32>>(),
                    inverse,
                );

                acc.iter()
                    .filter(|byte| byte[index] == popular)
                    .cloned()
                    .collect::<Vec<Vec<i32>>>()
            })
            .iter()
            .map(|byte| self.to_decimal(&byte.iter().join("")))
            .sum::<i32>()
    }

    fn render(&self, input: &[String]) -> i32 {
        self.to_decimal(
            &self
                .transpose(&self.input_to_bits(input))
                .iter()
                .map(|channel| self.popular(channel, false))
                .join(""),
        )
    }

    fn transpose<T>(&self, input: &[Vec<T>]) -> Vec<Vec<T>>
    where
        T: Clone,
    {
        (0..input[0].len())
            .map(|index| {
                input
                    .iter()
                    .map(|inner| inner[index].clone())
                    .collect::<Vec<T>>()
            })
            .collect()
    }

    fn input_to_bits(&self, input: &[String]) -> Vec<Vec<i32>> {
        input
            .iter()
            .map(|byte| {
                byte.chars()
                    .map(|bit| bit.to_string().parse::<i32>().unwrap())
                    .collect()
            })
            .collect()
    }

    fn to_decimal(&self, input: &str) -> i32 {
        i32::from_str_radix(input, 2).unwrap()
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
