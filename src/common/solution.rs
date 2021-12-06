// src/common/solution.rs

use std::{str::FromStr};

pub trait Solution<T, U> {
    fn read_input(&self, file_name: &str) -> Vec<T>
    where 
        T: FromStr,
        <T as FromStr>::Err: std::fmt::Debug {
        std::fs::read_to_string(file_name)
            .expect("file not found!")
            .lines()
            .map(|x| x.parse().unwrap())
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

    fn pt_1(&self, input: &[T]) -> U
    where 
        T: FromStr + std::cmp::PartialOrd,
        <T as FromStr>::Err: std::fmt::Debug;

    fn pt_2(&self, input: &[T]) -> U
    where 
        T: FromStr + std::cmp::PartialOrd,
        <T as FromStr>::Err: std::fmt::Debug;
}

