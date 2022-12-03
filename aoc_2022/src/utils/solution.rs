// src/solution/solution.rs

use std::fmt::Debug;
use std::fs::read_to_string;
use std::str::FromStr;
use std::time::Instant;

use super::reader::Reader;

pub trait Solution {
    type Input;
    type Output;

    fn file_name(&self) -> &'static str;

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output;

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output;

    fn measure_pt_1(&self, input: &[Self::Input]) -> (Self::Output, f32) {
        let now = Instant::now();
        (self.pt_1(&input), now.elapsed().as_secs_f32())
    }

    fn measure_pt_2(&self, input: &[Self::Input]) -> (Self::Output, f32) {
        let now = Instant::now();
        (self.pt_2(&input), now.elapsed().as_secs_f32())
    }
}

impl<S: Solution> Reader for S
where
    <S as Solution>::Input: FromStr,
    <<S as Solution>::Input as FromStr>::Err: Debug,
{
    type Data = <S as Solution>::Input;

    fn read(&self) -> Vec<Self::Data> {
        read_to_string(self.file_name())
            .expect("file not found!")
            .lines()
            .map(|x| x.parse().unwrap())
            .collect()
    }
}

#[cfg(test)]
pub mod validation {
    use super::Solution;
    use crate::{utils::reader::Reader, utils::validator::validator::Validator};
    use std::{fmt::Debug, str::FromStr};

    impl<S: Solution> Validator for S
    where
        <S as Solution>::Input: FromStr,
        <<S as Solution>::Input as FromStr>::Err: Debug,
        <S as Solution>::Output: Debug + PartialEq,
    {
        type Output = <S as Solution>::Output;

        fn validate(&self, pt1: Self::Output, pt2: Self::Output) {
            let input = self.read();
            let results = vec![
                (self.pt_1(&input), pt1),
                (self.pt_2(&input), pt2),
            ];
            results.iter().for_each(|test| assert_eq!(test.0, test.1))
        }
    }
}
