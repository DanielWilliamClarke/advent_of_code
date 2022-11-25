mod days;
mod utils {
    pub mod presentation;
    pub mod solution;
}

use days::{Day00, Day01};
use utils::{
    presentation::Presentation, 
    solution::Solution
};

fn main() {
    vec![
        Presentation::new(Box::new(Day00::new())).display(),
        Presentation::new(Box::new(Day01::new())).display(),
    ]
    .iter()
    .enumerate()
    .for_each(|(index, runner)| {
        runner(&format!("src/days/input/day_{}.txt", index));
    });
}
