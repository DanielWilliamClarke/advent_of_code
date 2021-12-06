// src/day_03/solution.rs

use crate::common::Solution;
use itertools::Itertools;

pub struct Day03 {}

impl Solution<String, i32> for Day03 {
    fn pt_1(&self, input: &[String]) -> i32 {
        let value = self.calculate(&self.transpose(self.input_to_bits(input)));
        value * (value ^ 0xFFF)
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        todo!()
    }
}

impl Day03 {
    pub fn new() -> Day03 {
        Day03 {}
    }

    fn calculate(&self, input: &[Vec<i32>]) -> i32 {
        self.render(input, |average| if average >= 0.5 { 1 } else { 0 })
    }

    fn render<F>(&self, input: &[Vec<i32>], criteria: F) -> i32
    where
        F: Fn(f32) -> i32,
    {
        let byte = input
            .iter()
            .map(|channel| criteria(channel.iter().sum::<i32>() as f32 / channel.len() as f32))
            .join("");

        i32::from_str_radix(&byte, 2).unwrap()
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

    fn transpose<T>(&self, v: Vec<Vec<T>>) -> Vec<Vec<T>>
    where
        T: Clone,
    {
        (0..v[0].len())
            .map(|i| v.iter().map(|inner| inner[i].clone()).collect::<Vec<T>>())
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_03::solution::Day03};

    #[test]
    fn solution_is_correct() {
        let day02 = Day03::new();
        let input = day02.read_input("src/day_03/input.txt");
        vec![
            (day02.pt_1(&input), 1131506),
        ]
        .iter()
        .for_each(|test| assert_eq!(test.0, test.1))
    }
}
