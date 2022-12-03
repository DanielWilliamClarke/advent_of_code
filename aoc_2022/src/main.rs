#![feature(arbitrary_enum_discriminant)]

mod days;
mod utils {
    pub mod printer;
    pub mod reader;
    pub mod solution;
    pub mod validator;
}

use std::fmt::Display;

use days::{Day00, Day01, Day02, Day03};
use utils::printer::Printer;


fn main() {
    let solutions: Vec<&dyn Display> = vec![
        &Printer(Day00),
        &Printer(Day01),
        &Printer(Day02),
        &Printer(Day03),
    ];

    solutions
        .iter()
        .for_each(|solution| {
            println!("{}", solution)
        });
}
