use std::{collections::HashSet, ops::{Add, Sub, AddAssign, SubAssign}};
use std::hash::{Hash};

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

#[derive(Hash, PartialEq, Clone, Eq)]
struct Coordinate {
    x: isize,
    y: isize
}

impl Coordinate {
    fn new (x: isize, y: isize) -> Self {
        Coordinate { x, y }
    }

    fn mag(&self) -> f32 {
        ((self.x.pow(2) + self.y.pow(2)) as f32).sqrt()
    }

    fn unit (&self) -> Self {
        let mag = self.mag();

        let x = self.x as f32 / mag;
        let x = if x < 0.0 { x.floor() } else { x.ceil() };
        let y = self.y as f32 / mag;
        let y = if y < 0.0 { y.floor() } else { y.ceil() };

        Coordinate::new(x as isize, y as isize)
    }

    fn distance_to(&self, rhs: &Self) -> isize {
        (self.to_owned() - rhs.to_owned()).mag() as isize
    }
}

impl Add for Coordinate {
    type Output = Coordinate;

    fn add(self, rhs: Self) -> Self::Output {
        Coordinate::new( self.x + rhs.x, self.y + rhs.y)
    }
}

impl AddAssign for Coordinate {
    fn add_assign(&mut self, rhs: Self) {
        let result = self.to_owned() + rhs;
        self.x = result.x;
        self.y = result.y;
    }
}

impl Sub for Coordinate {
    type Output = Coordinate;

    fn sub(self, rhs: Self) -> Self::Output {
        Coordinate::new( self.x - rhs.x, self.y - rhs.y)
    }
}

impl SubAssign for Coordinate {
    fn sub_assign(&mut self, rhs: Self) {
        let result = self.to_owned() - rhs;
        self.x = result.x;
        self.y = result.y;
    }
}

struct Rope {
    knots: Vec<Coordinate>,
}

impl Rope {
    fn new(size: usize) -> Self {
        Rope {
            knots: (0..size).map(|_| Coordinate::new(0, 0)).collect(),
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
        self.knots[0] += Coordinate::new(0, 1);
        self.drag()
    }

    fn east(&mut self) -> Coordinate {
        self.knots[0] += Coordinate::new(1, 0);
        self.drag()
    }

    fn south(&mut self) -> Coordinate {
        self.knots[0] -= Coordinate::new(0, 1);
        self.drag()
    }

    fn west(&mut self) -> Coordinate {
        self.knots[0] -= Coordinate::new(1, 0);
        self.drag()
    }

    fn drag(&mut self) -> Coordinate {
        (1..self.knots.len()).for_each(|index| {
            self.knots[index] = self.find_tail(
                self.knots[index - 1].clone(), 
                self.knots[index].clone()
            );
        });

        self.knots.last().unwrap().clone()
    }

    fn find_tail(
        &mut self,
        head: Coordinate,
        tail: Coordinate,
    ) -> Coordinate {
        match head.distance_to(&tail) {
            2.. => tail.clone() + (head - tail.clone()).unit(),
            _ => tail
        }
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
}

pub struct Day09;

impl Solution for Day09 {
    type Input = String;
    type Output1 = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_9.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output1 {
        self.follow_tail::<2>(input)
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output2 {
        self.follow_tail::<10>(input)
    }
}

impl Day09 {
    fn follow_tail<const SIZE: usize>(&self, input: &[String]) -> usize {
        self.parse(input)
            .iter()
            .fold(
                (Rope::new(SIZE), HashSet::<Coordinate>::new()),
                |(mut rope, mut visited), movement| {
                    visited.extend(rope.apply(movement));

                    (rope, visited)
                },
            )
            .1
            .len()
    }

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
        //6011
        Day09 {}.validate(6011, 2419);
    }
}
