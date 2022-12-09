#![feature(arbitrary_enum_discriminant)]

mod days;
mod utils {
    pub mod printer;
    pub mod reader;
    pub mod solution;
    pub mod validator;
}

use std::fmt::Display;

use days::{Day00, Day01, Day02, Day03, Day04, Day05, Day06, Day07, Day08, Day09};
use utils::printer::Printer;


fn main() {
    let solutions: Vec<&dyn Display> = vec![
        &Printer(Day00),
        &Printer(Day01),
        &Printer(Day02),
        &Printer(Day03),
        &Printer(Day04),
        &Printer(Day05),
        &Printer(Day06),
        &Printer(Day07),
        &Printer(Day08),
        &Printer(Day09),
    ];

    solutions
        .iter()
        .for_each(|solution| {
            println!("{}", solution)
        });
}
