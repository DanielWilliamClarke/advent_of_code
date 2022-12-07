use std::collections::HashSet;

// src/days/day_00/solution.rs
use crate::utils::solution::Solution;


pub struct Day06;

impl Solution for Day06 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_6.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.process_signal::<4>(&input[0]).unwrap_or(0)
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.process_signal::<14>(&input[0]).unwrap_or(0)
    }
}

impl Day06 {
    fn process_signal<const LEN: usize>(&self, stream: &str) -> Option<usize> {
        let mut buffer = Vec::<char>::new();
        buffer.reserve(LEN);

        'n: for i in 0..stream.len() {
            for bit in stream[i..i+LEN].chars() {
                if buffer.contains(&bit) {
                    buffer.clear();
                    continue 'n;
                }

                buffer.push(bit);
            }

            if buffer.len() == LEN {
                return Some(i + buffer.len());
            }
        }

        None
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day06};

    #[test]
    fn solution_is_correct() {
        Day06 {}.validate(1140, 3495);
    }
}
