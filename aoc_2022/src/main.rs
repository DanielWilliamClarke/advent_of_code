mod day_00;
mod day_01;
mod solution;

use day_00::Day00;
use day_01::Day01;
use solution::{Solution, Presentation};

fn main() {
    vec![
        Presentation::display(Day00::new()),
        Presentation::display(Day01::new()),
    ].iter()
    .enumerate()
    .for_each(|(index, runner)| {
        runner(&format!("src/day_0{}/input.txt", index));
    });
}
