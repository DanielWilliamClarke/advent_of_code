// src/solution/solution.rs

use std::any::type_name;
use std::fmt::{Debug, Display};
use std::fs::read_to_string;
use std::str::FromStr;

use super::printer::Printer;
use super::reader::Reader;

pub trait Solution {
    type Input;
    type Output;

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output;

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output;
}

impl<S: Solution> Reader for S
where
    <S as Solution>::Input: FromStr,
    <<S as Solution>::Input as FromStr>::Err: Debug,
{
    type Data = <S as Solution>::Input;

    fn read(&self, file_name: &str) -> Vec<Self::Data> {
        read_to_string(file_name)
            .expect("file not found!")
            .lines()
            .map(|x| x.parse().unwrap())
            .collect()
    }
}

impl<S: Solution> Printer for S
where
    <S as Solution>::Input: FromStr,
    <<S as Solution>::Input as FromStr>::Err: Debug,
    <S as Solution>::Output: Display,
{
    fn print(&self, file_name: &str) {
        self.div();
        println!(
            "     🎅 Running Advent Of Code 2022: {} 🎅",
            type_name::<S>()
        );
        self.div();
        let input = self.read(file_name);
        println!("     🥁 Part 1 result: {}", self.pt_1(&input));
        println!("     🥁 Part 2 result: {}", self.pt_2(&input));
        self.div();
    }
}

#[cfg(test)]
pub mod validation {
    use super::Solution;
    use crate::{utils::validator::validator::Validator, utils::reader::Reader};
    use std::{fmt::Debug, str::FromStr};

    impl<S: Solution> Validator for S
    where
        <S as Solution>::Input: FromStr,
        <<S as Solution>::Input as FromStr>::Err: Debug,
        <S as Solution>::Output: Debug + PartialEq,
    {
        type Output = <S as Solution>::Output;

        fn validate(&self, file_name: &str, expectations: (Self::Output, Self::Output)) {
            let input = self.read(file_name);
            let results = vec![
                (self.pt_1(&input), expectations.0),
                (self.pt_2(&input), expectations.1),
            ];
            results.iter().for_each(|test| assert_eq!(test.0, test.1))
        }
    }
}
