mod days;
mod utils {
    pub mod printer;
    pub mod reader;
    pub mod solution;
    pub mod validator;
}

use days::{Day00, Day01};
use utils::{
    printer::Printer, 
};

fn main() {
    let solutions: Vec<&dyn Printer> = vec![
        &Day00,
        &Day01,
    ];

    solutions
        .iter()
        .enumerate()
        .for_each(|(index, solution)| {
            solution.print(&format!("src/days/input/day_{}.txt", index));
        });
}
