// src/solution/solution.rs

use std::{str::FromStr};
use std::fs::read_to_string;
use std::fmt::Debug;

pub trait Solution<T, U> {
    fn new() -> Self;

    fn pt_1(&self, input: &[T]) -> U;

    fn pt_2(&self, input: &[T]) -> U;

    fn read_input(&self, file_name: &str) -> Vec<T>
    where
        T: FromStr,
        <T as FromStr>::Err: Debug,
    {
        read_to_string(file_name)
            .expect("file not found!")
            .lines()
            .map(|x| x.parse().unwrap())
            .collect()
    }
}
