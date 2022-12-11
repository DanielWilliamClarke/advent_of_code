// src/days/day_03/solution.rs

use std::collections::HashSet;
use crate::utils::solution::Solution;

pub struct Day03;

impl Solution for Day03 {
    type Input = String;
    type Output1 = u32;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_3.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output1 {
        self.prioritize(input)
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output2 {
        self.find_badges(input)
    }
}

impl Day03 {
    fn prioritize(&self, input: &[String]) -> u32 {
        input
            .iter()
            .fold(0, |acc, backpack| {
                let compartments = backpack.split_at(backpack.len() / 2);
                let left = self.categorize(compartments.0);
                let right = self.categorize(compartments.1);

                acc + left
                    .intersection(&right)
                    .into_iter()
                    .fold(0, |acc, mismatch| {
                        acc + self.bucket_priority(mismatch)
                    })
            })
    }

    fn find_badges(&self, input: &[String]) -> u32 {
        input
            .chunks(3)
            .fold(0, |acc, group| {
                let group = (
                    self.categorize(&group[0]),
                    self.categorize(&group[1]),
                    self.categorize(&group[2])
                );

                acc + group.0
                    .intersection(&group.1)
                    .cloned()
                    .collect::<HashSet<char>>()
                    .intersection(&group.2)
                    .fold(0, |acc, badge| acc + self.bucket_priority(badge))
            })
    }

    fn categorize(&self, compartment: &str) -> HashSet<char> {
        compartment
            .chars()
            .into_iter()
            .collect::<HashSet<char>>()
    }

    fn bucket_priority(&self, mismatch: &char) -> u32 {
        let shifted = *mismatch as u8 + 1;
        (match mismatch {
            'a'..='z' => shifted - b'a', //97 +
            'A'..='Z' => shifted - b'A' + (b'Z' - b'A') + 1,
            _ => 0,
        }) as u32
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day03};

    #[test]
    fn solution_is_correct() {
        Day03 {}.validate(8185, 2817);
    }
}
