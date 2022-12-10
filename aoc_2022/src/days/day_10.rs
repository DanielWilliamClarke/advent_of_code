// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

pub struct Day10;

impl Solution for Day10 {
    type Input = String;
    type Output = isize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_10.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        let stream = self.parse(input, 2);
        self.extract(stream, vec![20, 60, 100, 140, 180, 220])
    }

    fn pt_2(&self, _: &[Self::Input]) -> Self::Output {
        0
    }
}

impl Day10 {
    fn parse(&self, input: &[String], cycles: usize) -> Vec<isize> {
        input
            .iter()
            .fold(vec![1 as isize], |mut acc, command| {
                let mut command = command.split_whitespace();

                match command.next().unwrap() {
                    "addx" => {
                         let value = command.next().unwrap().parse::<isize>().unwrap();
                         (1..=cycles).fold(acc, |mut acc, index| {
                            let cycle_value = match index {
                                2 =>  acc.last().unwrap().clone() + value, 
                                _ => acc.last().unwrap().clone()
                            };
                            acc.push(cycle_value);
                            acc
                         })
                    }
                    _ => {
                        acc.push(acc.last().unwrap().clone());
                        acc
                    }
                }
            })
    }

    fn extract (&self, stream: Vec<isize>, sampling: Vec<usize>) -> isize {
        sampling
            .iter()
            .fold(0, |acc, sample_index| {
                acc + (stream.get(sample_index  - 1).unwrap() * *sample_index as isize)
            })
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day10, utils::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day10{}.validate(0, 0);
    }
}
