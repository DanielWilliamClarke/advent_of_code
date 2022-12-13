#![feature(arbitrary_enum_discriminant)]
#![feature(associated_type_defaults)]

mod days;
mod utils {
    pub mod printer;
    pub mod reader;
    pub mod solution;
    pub mod validator;
}

use std::fmt::Display;

use days::{Day00, Day01, Day02, Day03, Day04, Day05, Day06, Day07, Day08, Day09, Day10, Day11, Day12, Day13, /*USE*/};
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
        &Printer(Day10),
        &Printer(Day11), 
        &Printer(Day12), 
        &Printer(Day13), 
        /*PRINTER*/
    ];

    solutions
        .iter()
        .for_each(|solution| println!("{}", solution));
}
