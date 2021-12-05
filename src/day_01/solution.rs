// src/day_01/solution.rs

use crate::day_01::input::get;

use itertools::Itertools;

pub fn solution_pt_1() -> i32 {
    let input = get();
    println!("Length of day_01 input = {}", input.len());

    let result = input
        .iter()
        .fold(
        (0, 0), 
        |(total, previous), current| {
            let is_greater = previous != 0 && current > &previous;
            let total = if is_greater { total + 1 } else { total };
            (total, *current)
        });

    result.0
}

pub fn solution_pt_2() -> i32 {
    let input = get();
    println!("Length of day_01 input = {}", input.len());

    let result = input
        .iter()
        .tuple_windows::<(_,_,_)>()
        .fold(
        (0, 0),  
        |(total, previous), current| {
            let sum = current.0 + current.1 + current.2;
            let is_greater = previous != 0 && sum > previous;
            let total = if is_greater { total + 1 } else { total };
            (total, sum)
        });

    result.0
}

#[cfg(test)]
mod tests {
    use crate::day_01::{input::get, solution_pt_1, solution_pt_2};

    #[test]
    fn solution_pt_1_total_increases_greater_than_0_and_less_than_len() {
        let result = solution_pt_1();
        assert!(result > 0);
        assert!((result as usize) < get().len());
    }   
    
    #[test]
    fn solution_pt_1_total_is_solution_result() {
        assert_eq!(solution_pt_1(), 1393);
    }

    #[test]
    fn solution_pt_2_total_increases_greater_than_0_and_less_than_len() {
        let result = solution_pt_2();
        assert!(result > 0);
        assert!((result as usize) < get().len());
    }   
    
    #[test]
    fn solution_pt_2_total_is_solution_result() {
        assert_eq!(solution_pt_2(), 1359);
    }
}