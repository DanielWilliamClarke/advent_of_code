use itertools::Itertools;

use crate::common::Solution;

#[derive(Copy, Clone, Debug)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn new (x: i32, y: i32) -> Point {
        Point{x, y}
    } 
}

pub struct Day05 {}

impl Solution<String, i32> for Day05{
    fn pt_1(&self, input: &[String]) -> i32 {

        let points = self.parse(input);
        // println!("{:?}", points);

        0
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        0
    }
}

impl Day05 {
    pub fn new() -> Day05 {
        Day05 {}
    }

    fn parse (&self, input: &[String]) -> Vec<Vec<Point>> {
        input
            .iter()
            .map(|line| {
                line
                    .split(" -> ")
                    .map(|coordinate| {
                        let mut split = coordinate.split(',');
                        Point::new(
                            self.str_i32(split.next().unwrap()),
                            self.str_i32(split.next().unwrap()))
                    })
                    .collect::<Vec<Point>>()
            })
            .collect::<Vec<Vec<Point>>>()
    }

    fn str_i32(&self, input: &str) -> i32 {
        input.to_string().parse::<i32>().unwrap()
    }
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_05::solution::Day05};

    #[test]
    fn solution_is_correct() {
        let day05 = Day05::new();
        let input = day05.read_input("src/day_05/input.txt");
        vec![(0, 0)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
