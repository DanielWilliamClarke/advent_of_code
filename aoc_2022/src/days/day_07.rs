// src/days/day_00/solution.rs
use crate::utils::solution::Solution;
use std::{borrow::{BorrowMut, Borrow}, cell::RefCell, collections::HashMap, rc::Rc, slice::{Iter, IterMut}};

#[derive(Clone, Debug)]
struct FileSystem<'a> {
    pub parent: Option<&'a Box<FileSystem<'a>>>,
    pub dirs: HashMap<String, Option<&'a Box<FileSystem<'a>>>>,
    pub files: HashMap<String, usize>,

    pub size: usize,
}

impl<'a> FileSystem<'a> {
    fn new(parent: Option<&'a Box<FileSystem<'a>>>) -> Self {
        Self {
            parent,
            dirs: HashMap::new(),
            files: HashMap::new(),
            size: 0,
        }
    }

    fn build(mut self, mut instruction: IterMut<String>) -> Self {
        let mut command = match instruction.next() {
            Some(instruction) => {
                println!("{}", instruction); 
                instruction.split_whitespace()
            }
            None => return self,
        };

        let op = command.next().unwrap();
        let op_2 = command.next().unwrap();
        match op {
            "$" => match op_2 {
                    "cd" => {
                        let op_3 = command.next().unwrap();
                        match op_3 {
                            "/" => self.build(instruction),
                            ".." => self.parent.unwrap().build(instruction),
                            dir @ _ => self.dirs[dir].as_ref().unwrap().build(instruction),
                        }
                    }
                    // "ls" => {
                    //     self
                    // }
                    _ => self.build(instruction)
                },
            "dir" => {
                self.dirs.insert(
                    op_2.to_string(),
                    Some(&Box::new(FileSystem::new(Some(&Box::new(self))))),
                );
                self.build(instruction)
            }
            size @ _ => {
                self.files.insert(
                    op_2.to_string(),
                    size.parse::<usize>().unwrap(),
                );
                self.build(instruction) 
            }
        }
    }

    fn find_root(&mut self) -> &Self {
        while let Some(p) = self.parent {
            self = &mut p.find_root();
        }

        self
    }

    fn size(&mut self) -> &Self {
        let self_size = self.files.iter().map(|(_, v)| v).sum::<usize>();

        // size of all children
        self.size = self.dirs.iter().fold(self_size, |acc, (_, mut dir)| {
            acc + dir.unwrap().size().size
        });

        // size of self
        self
    }

    fn sum<const THRESHOLD: usize>(&self) -> usize {
        self.dirs
            .iter()
            .filter_map(|(_, dir)| -> Option<usize> {
                let size = dir.unwrap().size;
                if size >= THRESHOLD {
                    return Some(size);
                }
                None
            })
            .sum::<usize>()
    }
}

pub struct Day07;

impl Solution for Day07 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_7.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        FileSystem::new(None)
            .build(input.to_owned().iter_mut())
            .find_root()
            .size()
            .sum::<1_00_000>()
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        let a = input.iter();
        0
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day07};

    #[test]
    fn solution_is_correct() {
        Day07 {}.validate(0, 0);
    }
}
