// src/days/day_00/solution.rs
use crate::utils::solution::Solution;
use onig::{Captures, Regex};

enum CraneModel {
    CM9000,
    CM9001,
}

use CraneModel::*;

type Stacks = Vec<Vec<char>>;

#[derive(Debug)]
struct Instruction {
    pub quantity: usize,
    pub from: usize,
    pub to: usize,
}

pub struct Day05;

impl Solution for Day05 {
    type Input = String;
    type Output = String;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_5.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.stack_crates(input, CM9000)
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.stack_crates(input, CM9001)
    }
}

impl Day05 {
    fn stack_crates(&self,  input: &[String], model: CraneModel) -> String {
        let split_input = self.split_input(input);

        let mut stacks = self.parse_stacks(split_input[0]);
        let instructions = self.parse_instructions(split_input[1]);

        self.rearrange_crates(&mut stacks, instructions, model)
            .to_owned()
            .iter_mut()
            .map(|stack| stack.pop().unwrap())
            .collect()
    }

    fn split_input<'a>(&self, input: &'a [String]) -> Vec<&'a [String]> {
        input.split(|line| line.is_empty()).collect::<Vec<_>>()
    }

    fn parse_stacks(&self, stacks: &[String]) -> Stacks {
        // Parse the stacks ignoring the index row at the bottom
        let rows = stacks[0..stacks.len() - 1]
            .iter()
            .map(|row| {
                row.chars()
                    .collect::<Vec<_>>()
                    .chunks(4)
                    .map(|chunk| chunk[1]) // this hack though
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();

        // transpose and compact rows into stacks for easier sorting
        (0..rows[0].len())
            .map(|index| rows
                .iter()
                .map(|item| item[index])
                .rev()
                .filter(|item| item != &' ')
                .collect::<Vec<_>>()
            )
            .collect::<Vec<_>>()
    }

    fn parse_instructions(&self, instructions: &[String]) -> Vec<Instruction> {
        let regex = Regex::new("move (\\d*) from (\\d*) to (\\d*)").unwrap();

        fn get_nr(cap: &Captures, i: usize) -> usize {
            cap.at(i).unwrap().parse::<usize>().unwrap()
        }

        instructions
            .iter()
            .map(|instruction| {
                let captures = regex.captures(instruction).unwrap();
                Instruction {
                    quantity: get_nr(&captures, 1),
                    from: get_nr(&captures, 2) - 1, // transform number to index
                    to: get_nr(&captures, 3) - 1,
                }
            })
            .collect::<Vec<_>>()
    }

    fn rearrange_crates(&self, stacks: &mut Stacks, instructions: Vec<Instruction>, model: CraneModel) -> Stacks {
        instructions 
            .iter() 
            .for_each(|instruction| {
                let drain_index = stacks[instruction.from].len() - instruction.quantity; 
                let detached =  stacks[instruction.from].drain(drain_index..);

                let mut detached = match model {
                    CM9000 => detached.rev().collect(),
                    CM9001 => detached.collect(),
                };

                stacks[instruction.to].append(&mut detached);
            });

        stacks.clone()
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day05};

    #[test]
    fn solution_is_correct() {
        Day05 {}.validate("BWNCQRMDB".to_string(), "NHWZCBNBF".to_string());
    }
}
