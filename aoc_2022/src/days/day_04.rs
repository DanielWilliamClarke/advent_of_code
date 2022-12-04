// src/days/day_04/solution.rs
use crate::utils::solution::Solution;
use std::collections::HashSet;
pub struct Day04;

impl Solution for Day04 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_4.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.count_full_intersections(input)
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.count_all_intersections(input)
    }
}

impl Day04 {
    fn count_full_intersections(&self, input: &[String]) -> usize {
        input
            .iter()
            .filter(|zones| {
                let zones = self.expand_ranges(zones);
                let intersection = zones.0.intersection(&zones.1).cloned().collect::<HashSet<usize>>();   
                intersection == zones.1 || intersection == zones.0
            })
            .collect::<Vec<&String>>()
            .len()
    }

    fn count_all_intersections(&self, input: &[String]) -> usize {
        input
            .iter()
            .filter(|zones| {
                let zones = self.expand_ranges(zones);
                let intersection = zones.0.intersection(&zones.1).cloned().collect::<HashSet<usize>>();   
                !intersection.is_empty()
            })
            .collect::<Vec<&String>>()
            .len()
    }

    fn expand_ranges (&self, zones: &str) -> (HashSet<usize>, HashSet<usize>) {
        let mut zones = zones
            .split(",")
                .map(|zone| {
                    let range = zone
                        .split("-")
                        .map(|number| number.parse().unwrap())
                        .collect::<Vec<usize>>();

                    (range[0]..=range[1]).collect::<HashSet<usize>>()
                });
        
        ( zones.next().unwrap(), zones.next().unwrap() )
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day04, utils::validator::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day04{}.validate(498, 859);
    }
}
