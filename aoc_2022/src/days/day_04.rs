// src/days/day_04/solution.rs
use crate::utils::solution::Solution;

type Zones = ((usize, usize), (usize, usize));

pub struct Day04;

impl Solution for Day04 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_4.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.count_overlaps(input, |(left, right)| {
            self.fully_overlaps(left, right) || self.fully_overlaps(right, left)
        })
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.count_overlaps(input, |(left, right)| self.overlaps(left, right))
    }
}

impl Day04 {
    fn count_overlaps<F>(&self, input: &[String], resolver: F) -> usize
    where
        F: Fn(Zones) -> bool,
    {
        input
            .iter()
            .filter(|zones| resolver(self.extract_ranges(zones)))
            .count()
    }

    fn extract_ranges(&self, zones: &str) -> Zones {
        let mut zones = zones.split(',').map(|zone| {
            zone.split('-')
                .map(|number| number.parse().unwrap())
                .collect::<Vec<_>>()
        });

        let left = zones.next().unwrap();
        let right = zones.next().unwrap();

        ((left[0], left[1]), (right[0], right[1]))
    }

    fn fully_overlaps(&self, left: (usize, usize), right: (usize, usize)) -> bool {
        // .....2.......6.....
        // .......3...5.......
        left.0 <= right.0 && left.1 >= right.1
    }

    fn overlaps(&self, left: (usize, usize), right: (usize, usize)) -> bool {
        // ......4....6...
        // ...3....5......
        left.1 >= right.0 && right.1 >= left.0
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day04};

    #[test]
    fn solution_is_correct() {
        Day04 {}.validate(498, 859);
    }
}
