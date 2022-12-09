use std::collections::HashSet;

// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

enum Movement {
    North(usize),
    East(usize),
    South(usize),
    West(usize),
}

use Movement::*;

impl Movement {
    fn new_from_tuple(movement: (&str, usize)) -> Self {
        match movement.0 {
            "U" => North(movement.1),
            "R" => East(movement.1),
            "D" => South(movement.1),
            "L" => West(movement.1),
            _ => panic!("unknown direction"),
        }
    }
}

type Coordinate = (isize, isize);

struct Rope {
    head: Coordinate, 
    tail: Coordinate,
}

impl Rope {
    fn new() -> Self {
        Rope {
            head: (0, 0),
            tail: (0, 0),
        }
    }

    fn apply(&mut self, movement: &Movement) -> HashSet<Coordinate> {
        let visited = HashSet::new();
        match movement {
            North(steps) => Self::move_in_direction(steps, visited, || self.north()),
            East(steps) => Self::move_in_direction(steps, visited, || self.east()),
            South(steps) => Self::move_in_direction(steps, visited, || self.south()),
            West(steps) => Self::move_in_direction(steps, visited, || self.west()),
        }
    }

    fn north(&mut self) -> Coordinate {
        let current_head = self.head.clone();
        self.head.1 += 1;
        self.move_tail(current_head)
    }

    fn east(&mut self) -> Coordinate {
        let current_head = self.head.clone();
        self.head.0 += 1;
        self.move_tail(current_head)
    }

    fn south(&mut self) -> Coordinate {
        let current_head = self.head.clone();
        self.head.1 -= 1;
        self.move_tail(current_head)
    }

    fn west(&mut self) -> Coordinate {
        let current_head = self.head.clone();
        self.head.0 -= 1;
        self.move_tail(current_head)
    }

    fn move_tail (&mut self, prev_head: Coordinate)  -> Coordinate {
        let distance = self.distance_between();
        if distance > 1 {
            self.tail = prev_head;
        }
        self.tail
    }

    fn move_in_direction(
        steps: &usize,
        visited: HashSet<Coordinate>,
        mut mover: impl FnMut() -> Coordinate,
    ) -> HashSet<Coordinate> {
        (0..*steps).into_iter().fold(visited, |mut visited, _| {
            visited.insert(mover());
            visited
        })
    }

    fn direction_between(&self) -> Coordinate {
        (self.head.0 - self.tail.0, self.head.1 - self.tail.1)
    }

    fn distance_between(&self) -> usize {
        let direction = self.direction_between();
        ((direction.0.pow(2) + direction.1.pow(2)) as f32).sqrt().abs() as usize
    }
}

pub struct Day09;

impl Solution for Day09 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_9.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.parse(input)
            .iter()
            .fold(
                (Rope::new(), HashSet::<Coordinate>::new()),
                |(mut rope, mut visited), movement| {
                    visited.extend(rope.apply(movement));

                    (rope, visited)
                },
            )
            .1
            .len()
    }

    fn pt_2(&self, _: &[Self::Input]) -> Self::Output {
        0
    }
}

impl Day09 {
    fn parse(&self, input: &[String]) -> Vec<Movement> {
        input
            .iter()
            .map(|movement| {
                let mut movement = movement.split_whitespace();
                Movement::new_from_tuple((
                    movement.next().unwrap(),
                    movement.next().unwrap().parse::<usize>().unwrap(),
                ))
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day09};

    #[test]
    fn solution_is_correct() {
        Day09 {}.validate(13, 0);
    }
}
