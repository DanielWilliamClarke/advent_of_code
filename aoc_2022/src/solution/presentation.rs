// src/solution/presentation.rs

use std::any::type_name;
use std::{str::FromStr};
use std::fmt::{Display, Debug};

use super::Solution;

pub struct Presentation;

impl Presentation {
    pub fn print_results<S, T, U>(solution: S, file_name: &str)
    where
        S: Solution<T, U>,
        T: FromStr,
        <T as FromStr>::Err: Debug,
        U: Display,
    {
        Presentation::print_div();
        println!("   🎅 Running Advent Of Code 2022: {} 🎅", type_name::<S>());
        Presentation::print_div();
        let input = solution.read_input(file_name);
        println!("   Part 1 result: {}", solution.pt_1(&input));
        println!("   Part 2 result: {}", solution.pt_2(&input));
        Presentation::print_div();
    }

    fn print_div() {
        println!("🎄{:=<1$}🎄", "", 70);
    }
}
