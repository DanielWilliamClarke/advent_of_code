// src/solution/presentation.rs

use std::any::type_name;
use std::{str::FromStr};
use std::fmt::{Display, Debug};

use crate::utils::solution::Solution;

pub struct Presentation<S> {
    solution: Box<S>,
}

impl<S> Presentation<S> {
    pub fn new (solution: Box<S>) -> Self {
        Presentation { solution }
    }

    // this method provides some indirection allowing use to push 
    // a bunch of these structs into a vector and iterate over them 
    pub fn display<T, U>(&self) -> Box<dyn Fn(&str) + '_>
    where
        S: Solution<T, U>,
        T: FromStr,
        U: Display,
        <T as FromStr>::Err: Debug {
        Box::new(
            |file_name| self.print_results(file_name)
        )
    }

    fn print_results<T, U>(&self, file_name: &str)
    where
        S: Solution<T, U>,
        T: FromStr,
        <T as FromStr>::Err: Debug,
        U: Display,
    {
        self.print_div();
        println!("     🎅 Running Advent Of Code 2022: {} 🎅", type_name::<S>());
        self.print_div();
        let input = self.solution.read_input(file_name);
        println!("     🥁 Part 1 result: {}", self.solution.pt_1(&input));
        println!("     🥁 Part 2 result: {}", self.solution.pt_2(&input));
        self.print_div();
    }

    fn print_div(&self) {
        println!("🎄{:=<1$}🎄", "", 70);
    }
}
