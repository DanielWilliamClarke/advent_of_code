// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

pub struct Day02;

#[derive(Clone, Copy)]
enum RPSState {
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
}

enum Outcome {
    WIN = 6,
    DRAW = 3,
    LOSS = 0
}

type Round = (RPSState, RPSState);

use RPSState::*;
use Outcome::*;

impl Solution for Day02 {
    type Input = String;
    type Output = i32;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_2.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.calculate_score(input, |_, instruction| self.interpret(instruction))
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.calculate_score(input, |opponent, instruction| self.anticpate(opponent, instruction))
    }
}

impl Day02 {
    fn calculate_score<F>(&self, input: &[String], resolver: F) -> i32
    where  
        F: Fn(RPSState, &str) -> RPSState
    {
        self.parse_rounds(input, resolver)
            .iter()
            .fold(0,|acc, round| acc + self.resolve_round(round))
    }

    fn parse_rounds<F>(&self, input: &[String], resolver: F) -> Vec<Round>
    where  
        F: Fn(RPSState, &str) -> RPSState
    {
        input
            .iter()
            .map(|round| {
                let mut split_iter = round.split_whitespace();

                let opponents_choice = self.interpret(split_iter.next().unwrap());
                let my_choice = resolver(opponents_choice, split_iter.next().unwrap());

                ( opponents_choice, my_choice )
            })
            .collect()
    }

    fn interpret(&self, instruction: &str) -> RPSState {
        match instruction {
            "A" | "X" => ROCK,
            "B" | "Y" => PAPER,
            "C" | "Z" => SCISSORS,
            _ => panic!("unknown state encountered")
        } 
    }
    
    fn anticpate(&self, opponent: RPSState, instruction: &str) -> RPSState {
        match (opponent, instruction) {
            (ROCK, "Y") | (PAPER, "X") | (SCISSORS, "Z") => ROCK,
            (ROCK, "Z") | (PAPER, "Y") | (SCISSORS, "X") => PAPER,
            (ROCK, "X") | (PAPER, "Z") | (SCISSORS, "Y") => SCISSORS,
            _ => panic!("unknown state encountered")
        }
    }

    fn resolve_round(&self, round: &Round) -> i32 {
        (round.1 as i32) + match round {
            (SCISSORS, ROCK) | (ROCK, PAPER) | (PAPER, SCISSORS) => WIN,
            (ROCK, SCISSORS) | (PAPER, ROCK) | (SCISSORS, PAPER) => LOSS,
            _ => DRAW
        } as i32
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day02, utils::validator::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day02{}.validate((10994, 12526));
    }
}
