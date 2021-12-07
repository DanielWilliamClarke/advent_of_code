// src/day_03/solution.rs

use crate::common::Solution;
use itertools::Itertools;

pub struct Day03 {}

impl Solution<String, i32> for Day03 {
    fn pt_1(&self, input: &[String]) -> i32 {
        let value =  self.render(&self.transpose(&self.input_to_bits(input)));
        value * (value ^ 0xFFF)
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        let bytes = self.input_to_bits(input);
        let transposed = self.transpose(&bytes);
        self.calculate(bytes.clone(), &transposed, false) * self.calculate(bytes, &transposed,  true)
    }
}

impl Day03 {
    pub fn new() -> Day03 {
        Day03 {}
    }

    fn calculate(&self, bytes: Vec<Vec<i32>>, transposed: &[Vec<i32>], inverse: bool) -> i32 {
        let a = (0..transposed.len())
            .map(|index| {
                let average = transposed[index].iter().sum::<i32>() as f32 / transposed[0].len() as f32;
                println!("average at {} is {}", index, average);
                let popular = if (average >= 0.5) ^ inverse { 1 } else { 0 };
                (index, popular)
            })
            .fold(bytes, |acc, (index, bit)| {
                println!("index: {} - len of acc: {}, current bit {}", index, acc.len(), bit);
                if acc.len() == 1 {
                    return acc;
                }

                acc  
                    .iter()
                    .filter(|byte| byte[index] == bit)
                    .cloned()
                    .collect::<Vec<Vec<i32>>>()
            })
            .iter()
            .map(|byte| self.to_decimal(&byte.iter().join("")))
            .sum::<i32>();
            
        println!("{}", a);
        a
    }

    fn render(&self, input: &[Vec<i32>]) -> i32 {
        self.to_decimal(
            &input
            .iter()
            .map(|channel| {
                let average = channel.iter().sum::<i32>() as f32 / channel.len() as f32;
                if average >= 0.5 { 1 } else { 0 }
            })
            .join(""))
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
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_03::solution::Day03};

    #[test]
    fn solution_is_correct() {
        let day02 = Day03::new();
        let input = day02.read_input("src/day_03/input.txt");
        vec![(day02.pt_1(&input), 1131506)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
