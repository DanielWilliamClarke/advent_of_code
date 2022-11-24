
mod solution;
mod day_00;

use day_00::Day00;
use solution::Solution;

fn main() {
    let solutions = vec![
        Day00::package()
    ];
    
    solutions
        .iter()
        .enumerate()
        .for_each(|(index, solution)| {
            solution(&format!("src/day_0{}/input.txt", index));
        });
}

