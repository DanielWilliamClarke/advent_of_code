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
        T: FromStr,
        <T as FromStr>::Err: std::fmt::Debug,
        U: std::fmt::Display {
        self.print_div();
        {
            println!("🎅 Running Advent Of Code: {} 🎅", std::any::type_name::<Self>());
        }
        self.print_div();
        {
            let input = self.read_input(file_name);
            println!("Part 1 result: {}", self.pt_1(&input));
            println!("Part 2 result: {}", self.pt_2(&input));
        }
        self.print_div();
        println!();
    }

    fn print_div (&self) {
        println!("🎄{:=<1$}🎄", "", 69 /* nice */);    
    } 

    fn pt_1(&self, input: &[T]) -> U;

    fn pt_2(&self, input: &[T]) -> U;
}

