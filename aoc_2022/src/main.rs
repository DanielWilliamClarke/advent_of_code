mod days;
mod utils {
    pub mod presentation;
    pub mod solution;
}

use days::{Day00, Day01};
use utils::{
    presentation::Presentation, 
};

fn main() {
    let solutions: Vec<&dyn Presentation> = vec![
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
