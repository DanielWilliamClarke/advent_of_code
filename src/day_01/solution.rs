// src/day_01/solution.rs


use std::{str::FromStr};
use itertools::Itertools;
use crate::common::Solution;

pub struct Day01 {}

impl Solution<i32, usize> for Day01 {
    fn pt_1(&self, input: &[i32]) -> usize
    where
        i32: FromStr + std::cmp::PartialOrd,
        <i32 as FromStr>::Err: std::fmt::Debug {
            input
                .iter()
                .tuple_windows::<(_,_)>()
                .filter(|(a, b)| b > a)
                .collect_vec()
                .len()
    }

    fn pt_2 (&self, input: &[i32]) -> usize 
    where
        i32: FromStr + std::cmp::PartialOrd,
        <i32 as FromStr>::Err: std::fmt::Debug {
        input
            .iter()
            .tuple_windows::<(_,_,_)>()
            .map(|(a, b, c)| a + b + c)
            .tuple_windows::<(_,_)>()
            .filter(|(a, b)| b > a)
            .collect_vec()
            .len()
    }
}

impl Day01 {
    pub fn new() -> Day01 {
        Day01 {}
    }
}

#[cfg(test)]
mod tests {
    use crate::{day_01::solution::Day01, common::Solution};

    #[test]
    fn solution_pt_1_total_increases_greater_than_0_and_less_than_len() {
        let day01 = Day01::new();
        let input = day01.read_input("src/day_01/input.txt");
        let result = day01.pt_1(&input);
        assert!(result > 0);
        assert!((result as usize) < input.len());
    }   
    
    #[test]
    fn solution_pt_1_total_is_solution_result() {
        let day01 = Day01::new();
        let input = day01.read_input("src/day_01/input.txt");
        let result = day01.pt_1(&input);
        assert_eq!(result, 1393);
    }

    #[test]
    fn solution_pt_2_total_increases_greater_than_0_and_less_than_len() {
        let day01 = Day01::new();
        let input = day01.read_input("src/day_01/input.txt");
        let result = day01.pt_2(&input);
        assert!(result > 0);
        assert!((result as usize) < input.len());
    }   
    
    #[test]
    fn solution_pt_2_total_is_solution_result() {
        let day01 = Day01::new();
        let input = day01.read_input("src/day_01/input.txt");
        let result = day01.pt_2(&input);
        assert_eq!(result, 1359);
    }
}