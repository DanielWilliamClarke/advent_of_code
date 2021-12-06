// src/day_02/solution.rs

use crate::common::Solution;
use std::str::FromStr;

#[derive(Default)]
struct Trajectory {
    pub position: i32,
    pub depth: i32,
    pub aim: i32,
}

impl Trajectory {
    pub fn combine(&self) -> i32 {
        self.position * self.depth
    }
}

pub struct Day02 {}

impl Solution<String, i32> for Day02 {
    fn pt_1(&self, input: &[String]) -> i32 {
        self.parse(input, |mut trajectory, direction, distance| -> Trajectory {
            match direction {
                "forward" => trajectory.position += distance,
                "down" => trajectory.depth += distance,
                "up" => trajectory.depth -= distance,
                _ => {}
            };
            trajectory
        })
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        self.parse(input, |mut trajectory, direction, distance| -> Trajectory {
            match direction {
                "forward" => {
                    trajectory.position += distance;
                    trajectory.depth += trajectory.aim * distance;
                }
                "down" => trajectory.aim += distance,
                "up" => trajectory.aim -= distance,
                _ => {}
            };
            trajectory
        })
    }
}

impl Day02 {
    pub fn new() -> Day02 {
        Day02 {}
    }

    fn parse<F>(&self, input: &[String], parser: F) -> i32
    where
        F: Fn(Trajectory, &str, i32) -> Trajectory,
    {
        input
            .iter()
            .map(|instruction| {
                let mut split = instruction.split(' ');
                (split.next().unwrap(), self.convert(split.next().unwrap()))
            })
            .fold(Trajectory::default(), |acc, (direction, distance)| {
                parser(acc, direction, distance)
            })
            .combine()
    }

    fn convert(&self, input: &str) -> i32 {
        <i32 as FromStr>::from_str(input).unwrap()
    }
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_02::solution::Day02};

    #[test]
    fn solution_pt_1_total_is_solution_result() {
        let day02 = Day02::new();
        let input = day02.read_input("src/day_02/input.txt");
        let result = day02.pt_1(&input);
        assert_eq!(result, 1868935);
    }

    #[test]
    fn solution_pt_2_total_is_solution_result() {
        let day02 = Day02::new();
        let input = day02.read_input("src/day_02/input.txt");
        let result = day02.pt_2(&input);
        assert_eq!(result, 1965970888);
    }
}
