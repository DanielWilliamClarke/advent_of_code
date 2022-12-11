use std::{cell::RefCell, rc::Rc};

// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

#[derive(Clone)]
struct Command {
    val: isize,
    cycles: usize
}

impl Command {
    fn new(val: isize, cycles: usize) -> Self {
        Command { val, cycles }
    }

    fn consume_cycle(&mut self) -> bool {
        self.cycles -= 1;

        if self.cycles == 0 { true } else { false }
    }
}

#[derive(Clone)]
enum Op {
    ADDX(Rc<RefCell<Command>>),
    NOOP
}

use Op::*;

pub struct Day10;

impl Solution for Day10 {
    type Input = String;
    type Output1 = usize;
    type Output2 = String;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_10.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output1 {
        let program = self.compile(input);
        let cycles = self.execute(&program);
        self.extract(&cycles, &vec![20, 60, 100, 140, 180, 220]).try_into().unwrap()
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output2 {
        let program = self.compile(input);
        let cycles = self.execute(&program);

        let clean_program = self.compile(input);
        let output = self.display::<40>(&clean_program, &cycles);

        output
            .iter()
            .map(|row| format!("\n{}", row.iter().collect::<String>()))
            .collect::<Vec<_>>()
            .join("")
    }
}

impl Day10 {
    fn compile(&self, input: &[String]) -> Vec<Op> {
        input
            .iter()
            .map(|command| {
                let mut command = command.split_whitespace();
                match command.next().unwrap() {
                    "addx" => {
                         let value = command.next().unwrap().parse::<isize>().unwrap();
                         ADDX(Rc::new(RefCell::new(Command::new(value, 2))))
                    }
                    _ => NOOP
                }
            })
            .collect()
    }

    fn execute(&self, program: &Vec<Op>) -> Vec<isize> {
        let mut output = vec![1];
        let mut program_iter = program.iter();
        let mut current_command = program_iter.next();

        loop {
            let command = match current_command {
                Some(command) => command,
                None => return output,
            };

            match command {
                ADDX(command) => {
                    let mut command = command.borrow_mut();
                    match command.consume_cycle() {
                        true => {
                            output.push(output.last().unwrap().clone() as isize + command.val);
                            current_command = program_iter.next();
                        },
                        false => {
                            output.push(output.last().unwrap().clone());
                        }
                    }
                },
                NOOP => {
                    output.push(output.last().unwrap().clone());
                    current_command = program_iter.next();
                },
            };
        }
    }

    fn extract (&self, stream: &Vec<isize>, sampling: &Vec<isize>) -> isize {
        sampling
            .iter()
            .fold(0, |acc, sample_index| {
                acc + (stream.get(*sample_index as usize  - 1).unwrap() * *sample_index)
            })
    }

    fn display<const COLS: usize>(&self, program: &Vec<Op>, cycles: &Vec<isize>) -> Vec<Vec<char>> {
        let mut display = (0..cycles.len() / COLS)
            .map(|_| (0..COLS).map(|_|'.').collect())
            .collect();

        let mut program_iter = program.iter();
        let mut current_command = program_iter.next();
        let mut register_iter = cycles.iter().enumerate();

        loop {
            let command = match current_command {
                Some(command) => command,
                None => return display,
            };

            let (cycle, x_register) = register_iter.next().unwrap();

            let row_index = cycle / COLS;
            let col_index = cycle % COLS;
            let row = display.get_mut(row_index).unwrap();    
            
            if col_index as isize >= x_register - 1 && col_index as isize <= x_register + 1 {
                row.insert(col_index, '#');
            } else {
                row.insert(col_index, '.');
            }

            match command {
                ADDX(command) => {
                    if command.borrow_mut().consume_cycle() == true  {
                        current_command = program_iter.next();
                    }
                },
                NOOP =>  current_command = program_iter.next()
            };
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::{
        Day10, utils::validator::Validator
    };

    #[test]
    fn solution_is_correct() {
        Day10{}.validate(
            14760, 
            String::from(
               "\n####.####..##..####.###..#..#.###..####.........................................\
                \n#....#....#..#.#....#..#.#..#.#..#.#............................................\
                \n###..###..#....###..#..#.#..#.#..#.###..........................................\
                \n#....#....#.##.#....###..#..#.###..#............................................\
                \n#....#....#..#.#....#.#..#..#.#.#..#............................................\
                \n####.#.....###.####.#..#..##..#..#.####........................................."
            )
        );
    }
}
