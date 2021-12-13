
use itertools::Itertools;

use crate::common::Solution;

type Line = (usize, usize, usize, usize);
type Streams = Vec<Line>;

pub struct Day05;

impl Solution<String, i32> for Day05 {
    fn pt_1(&self, input: &[String]) -> i32 {
        self.accumulate_overlaps(self.parse(input))
    }

    fn pt_2(&self, input: &[String]) -> i32 {
        0
    }
}

impl Day05 {
    pub fn new() -> Day05 {
        Day05 {}
    }

    fn parse(&self, input: &[String]) -> Streams {
        input
            .iter()
            .map(|line| {
                let points = line
                    .split(" -> ")
                    .map(|coordinate| {
                        let mut split = coordinate.split(',');
                        (
                            self.str_usize(split.next().unwrap()),
                            self.str_usize(split.next().unwrap()),
                        )
                    })
                    .collect::<Vec<(usize, usize)>>();

                let (x, y) = *points.first().unwrap();
                let (xx, yy) = *points.last().unwrap();

                (x.min(xx), y.min(yy), x.max(xx), y.max(yy))
            })
            .collect::<Streams>()
    }

    fn str_usize(&self, input: &str) -> usize {
        input.to_string().parse::<usize>().unwrap()
    }

    fn accumulate_overlaps(&self, points: Streams) -> i32 {
        let mut map = vec![0u8; 1000 * 1000];
        let mut overlaps = 0;

        let mut mark = |x: usize, y: usize| {
            if map[(x + y * 1000) as usize] == 1 {
                overlaps += 1;
            }
            map[(x + y * 1000) as usize] += 1;
        };

        points
            .iter()
            .for_each(|(x, y, xx, yy)| {
                if x == xx {
                    (*y..=*yy).for_each(|y| mark(*x, y));
                } else if y == yy {
                    (*x..=*xx).for_each(|x| mark(x, *y));
                }
            });

        overlaps
    } 
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_05::solution::Day05};

    #[test]
    fn solution_is_correct() {
        let day05 = Day05::new();
        let input = day05.read_input("src/day_05/input.txt");
        vec![(day05.pt_1(&input), 5167)]
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
