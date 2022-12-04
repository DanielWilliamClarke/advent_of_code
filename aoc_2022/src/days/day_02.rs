// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

pub struct Day02;

#[derive(Clone, Copy)]
enum RPS {
    Rock = 1,
    Paper = 2,
    Scissors = 3
}

enum Outcome {
    Win = 6,
    Draw = 3,
    Loss = 0
}

type Round = (RPS, RPS);

use RPS::*;
use Outcome::*;

impl Solution for Day02 {
    type Input = String;
    type Output = i32;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_2.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.calculate_score(input, &|_, instruction| self.interpret(instruction))
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.calculate_score(input, &|opponent, instruction| self.anticpate(opponent, instruction))
    }
}

impl Day02 {
    fn calculate_score<F>(&self, input: &[String], resolver: &F) -> i32
    where  
        F: Fn(&RPS, &str) -> RPS
    {
        input
            .iter()
            .fold(0, |acc, round| {
                let mut split_iter = round.split_whitespace();
                let opponents_choice = self.interpret(split_iter.next().unwrap());
                let my_choice = resolver(&opponents_choice, split_iter.next().unwrap());
                acc + self.resolve_round(&( opponents_choice, my_choice ))
            })
    }

    fn interpret(&self, instruction: &str) -> RPS {
        match instruction {
            "A" | "X" => Rock,
            "B" | "Y" => Paper,
            "C" | "Z" => Scissors,
            _ => panic!("unknown state encountered")
        } 
    }
    
    fn anticpate(&self, opponent: &RPS, instruction: &str) -> RPS {
        match (opponent, instruction) {
            (Rock, "Y") | (Paper, "X") | (Scissors, "Z") => Rock,
            (Rock, "Z") | (Paper, "Y") | (Scissors, "X") => Paper,
            (Rock, "X") | (Paper, "Z") | (Scissors, "Y") => Scissors,
            _ => panic!("unknown state encountered")
        }
    }

    fn resolve_round(&self, round: &Round) -> i32 {
        (round.1 as i32) + match round {
            (Scissors, Rock) | (Rock, Paper) | (Paper, Scissors) => Win,
            (Rock, Scissors) | (Paper, Rock) | (Scissors, Paper) => Loss,
            _ => Draw
        } as i32
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day02, utils::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day02{}.validate(10994, 12526);
    }
}
