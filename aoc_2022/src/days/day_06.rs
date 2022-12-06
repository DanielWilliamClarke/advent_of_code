// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

const START_OF_PACKET_LEN: usize = 4;
const START_OF_MESSAGE_LEN: usize = 14;

pub struct Day06;

impl Solution for Day06 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_6.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        self.process_signal(&input[0], START_OF_PACKET_LEN)
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        self.process_signal(&input[0], START_OF_MESSAGE_LEN)
    }
}

impl Day06 {
    fn process_signal(&self, stream: &str, marker_length: usize) -> usize {
        for mut i in 0..stream.len() {
            let mut buffer = "".to_string();

            for bit in stream[i..i+marker_length].chars() {
                if buffer.contains(bit) {
                    i = i + buffer.len();
                    break;
                }

                buffer.push(bit);
            }

            if buffer.len() == marker_length {
                return i + buffer.len();
            }
        }

        0
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
