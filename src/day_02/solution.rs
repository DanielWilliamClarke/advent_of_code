// src/day_02/solution.rs

use crate::common::Solution;
use std::str::FromStr;

#[derive(Default)]
struct Trajectory {
    position: i32,
    depth: i32,
    aim: i32,
}

impl Trajectory {
    pub fn new() -> Trajectory {
        Trajectory::default()
    }

    pub fn combine(&self) -> i32 {
        self.position * self.depth
    }

    pub fn update_position(&mut self, distance: &i32) {
        self.position += distance;
    }

    pub fn update_depth(&mut self, distance: &i32) {
        self.depth += distance;
    }

    pub fn update_aim(&mut self, distance: &i32) {
        self.aim += distance;
    }

    pub fn get_aim(&self) -> i32 {
        self.aim
    }
}

pub struct Day02 {}

impl Solution<String, i32> for Day02 {
    fn pt_1(&self, input: &[String]) -> i32 {
        self.parse(input, |mut trajectory, direction, distance| -> Trajectory {
            match direction {
                "forward" => trajectory.update_position(&distance),
                "down" => trajectory.update_depth(&distance),
                "up" => trajectory.update_depth(&-distance),
                _ => {}
            };
            trajectory
        })
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        self.parse(input, |mut trajectory, direction, distance| -> Trajectory {
            match direction {
                "forward" => {
                    trajectory.update_position(&distance);
                    trajectory.update_depth(&(trajectory.get_aim() * distance))
                }
                "down" => trajectory.update_aim(&distance),
                "up" => trajectory.update_aim(&-distance),
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

    fn parse<'a, F>(&self, input: &[String], parser: F) -> i32
    where
        F: Fn(Trajectory, &str, i32) -> Trajectory,
    {
        input
            .iter()
            .fold(Trajectory::new(), move |acc, movement| {
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
