// src/main.rs

mod common;
mod day_01;
mod day_02;

use common::Solution;
use day_01::Day01;
use day_02::Day02;

fn main() {
    Day01::new().run("src/day_01/input.txt");
    Day02::new().run("src/day_02/input.txt");
}
