mod days;
mod utils {
    pub mod printer;
    pub mod reader;
    pub mod solution;
    pub mod validator;
    pub mod timer;
}

use std::fmt::Display;

use days::{Day00, Day01};
use utils::printer::Printer;


fn main() {
    let solutions: Vec<&dyn Display> = vec![
        &Printer(Day00),
        &Printer(Day01),
    ];

    solutions
        .iter()
        .for_each(|solution| {
            println!("{}", solution)
        });
}
