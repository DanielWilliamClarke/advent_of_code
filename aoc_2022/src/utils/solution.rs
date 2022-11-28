// src/solution/solution.rs

use std::any::type_name;
use std::str::FromStr;
use std::fs::read_to_string;
use std::fmt::{Display, Debug};

use super::presentation::Printer;
use super::reader::Reader;

pub trait Solution {
    type Input;
    type Output;

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output;

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output;
}

impl <S: Solution> Reader for S
where
    <S as Solution>::Input: FromStr,
    <<S as Solution>::Input as FromStr>::Err: Debug,
{
    type Data = <S as Solution>::Input;

    fn read_input(&self, file_name: &str) -> Vec<Self::Data> {
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
    <S as Solution>::Output: Display
{
    fn print_results(&self, file_name: &str)
    {
        self.print_div();
        println!("     🎅 Running Advent Of Code 2022: {} 🎅", type_name::<S>());
        self.print_div();
        let input = self.read_input(file_name);
        println!("     🥁 Part 1 result: {}", self.pt_1(&input));
        println!("     🥁 Part 2 result: {}", self.pt_2(&input));
        self.print_div();
    }
}