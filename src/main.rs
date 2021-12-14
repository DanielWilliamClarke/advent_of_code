// src/main.rs

#![feature(int_abs_diff)]

mod common;
mod day_01;
mod day_02;
mod day_03;
mod day_04;
mod day_05;
mod day_06;

use common::Solution;
use day_01::Day01;
use day_02::Day02;
use day_03::Day03;
use day_04::Day04;
use day_05::Day05;
use day_06::Day06;

fn main() {
    Day01::new().run("src/day_01/input.txt");
    Day02::new().run("src/day_02/input.txt");
    Day03::new().run("src/day_03/input.txt");
    Day04::new().run("src/day_04/input.txt");
    Day05::new().run("src/day_05/input.txt");
    Day06::new().run("src/day_06/input.txt");
}
