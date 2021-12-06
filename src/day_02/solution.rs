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
            .fold(Trajectory::default(), |acc, movement| {
                let mut split = movement.split(' ');
                let direction = split.next().unwrap();
                let distance = <i32 as FromStr>::from_str(split.next().unwrap()).unwrap();
                parser(acc, direction, distance)
            })
            .combine()
    }
}

#[cfg(test)]
mod tests {}
