mod day_00;
mod day_01;
mod solution;

use day_00::Day00;
use day_01::Day01;
use solution::Solution;

fn main() {
    let solutions = vec![
        Day00::display(),
        Day01::display(),
    ];
    
    solutions
    .iter()
    .enumerate()
    .for_each(|(index, solution)| {
        solution(&format!("src/day_0{}/input.txt", index));
    });
}
