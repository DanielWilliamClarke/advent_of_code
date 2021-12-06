// src/common/solution.rs

use std::{str::FromStr};

pub trait Solution<T, U> {
    fn read_input(&self, file_name: &str) -> Vec<Result<T, <T as FromStr>::Err>>
    where 
        T: FromStr {
        std::fs::read_to_string(file_name)
            .expect("file not found!")
            .lines()
            .map(|x| x.parse())
            .collect()
    }

    fn run(&self, file_name: &str)
    where 
        T: FromStr + std::cmp::PartialOrd,
        <T as FromStr>::Err: std::fmt::Debug,
        U: std::fmt::Display {
        println!("Running Advent Of Code: {}", std::any::type_name::<Self>());

        let input = self.read_input(file_name);
        println!("Part 1 result: {}", self.pt_1(&input));
        println!("Part 2 result: {}", self.pt_2(&input));
    }

    fn pt_1(&self, input: &[Result<T, <T as FromStr>::Err>]) -> U
    where 
        T: FromStr + std::cmp::PartialOrd,
        <T as FromStr>::Err: std::fmt::Debug;

    fn pt_2(&self, input: &[Result<T, <T as FromStr>::Err>]) -> U
    where 
        T: FromStr + std::cmp::PartialOrd,
        <T as FromStr>::Err: std::fmt::Debug;
}

