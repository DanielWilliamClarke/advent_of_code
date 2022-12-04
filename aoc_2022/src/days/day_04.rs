// src/days/day_04/solution.rs
use crate::utils::solution::Solution;
use std::collections::HashSet;

type Zones = (HashSet<usize>, HashSet<usize>);

pub struct Day04;

impl Solution for Day04 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_4.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.count_overlaps(input, |intersection, zones| {
            intersection == zones.0 || intersection == zones.1
        })
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.count_overlaps(input, |intersection, _| !intersection.is_empty())
    }
}

impl Day04 {
    fn count_overlaps<F>(&self, input: &[String], resolver: F) -> usize
    where
        F: Fn(HashSet<usize>, Zones) -> bool,
    {
        input
            .iter()
            .filter(|zones| {
                let zones = self.expand_ranges(zones);
                let intersection = zones
                    .0
                    .intersection(&zones.1)
                    .cloned()
                    .collect::<HashSet<usize>>();
                resolver(intersection, zones)
            })
            .collect::<Vec<&String>>()
            .len()
    }

    fn expand_ranges(&self, zones: &str) -> Zones {
        let mut zones = zones.split(",").map(|zone| {
            let range = zone
                .split("-")
                .map(|number| number.parse().unwrap())
                .collect::<Vec<usize>>();

            (range[0]..=range[1]).collect::<HashSet<usize>>()
        });

        (zones.next().unwrap(), zones.next().unwrap())
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::validator::Validator, Day04};

    #[test]
    fn solution_is_correct() {
        Day04 {}.validate(498, 859);
    }
}
