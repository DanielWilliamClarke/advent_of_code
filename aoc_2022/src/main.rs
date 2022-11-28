mod days;
mod utils {
    pub mod presentation;
    pub mod reader;
    pub mod solution;
}
mod test_utils {
   pub mod validator;
}

use days::{Day00, Day01};
use utils::{
    presentation::Printer, 
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
            solution.print_results(&format!("src/days/input/day_{}.txt", index));
        });
}
