// src/days/day_00/solution.rs
use crate::utils::solution::Solution;
use std::{
    borrow::Borrow,
    cell::RefCell,
    collections::HashMap,
    rc::Rc,
};

#[derive(Clone, Debug)]
struct FileSystem {
    pub parent: Option<Rc<RefCell<FileSystem>>>,
    pub dirs: HashMap<String, Rc<RefCell<FileSystem>>>,
    pub files: HashMap<String, usize>, 
    pub size: usize,
}

impl FileSystem {
    fn new(parent: Option<Rc<RefCell<FileSystem>>>) -> Self {
        Self {
            parent,
            dirs: HashMap::new(),
            files: HashMap::new(),
            size: 0,
        }
    }

    fn add_dir(&mut self, name: String, dir: Rc<RefCell<FileSystem>>) {
        self.dirs.insert(name, dir);
    }

    fn add_file(&mut self, name: String, size: usize) {
        self.files.insert(name, size);
    }

    fn cd_into(&self, op: &str) -> Option<Rc<RefCell<FileSystem>>> {
        match op {
            "/" => Some(Rc::new(RefCell::new(FileSystem::new(None)))),
            ".." => Some(Rc::clone(self.parent.as_ref().borrow().unwrap())),
            dir => match self.dirs.get(dir) {
                Some(dir) => Some(Rc::clone(dir)),
                None => panic!("dir not found"),
            },
        }
    }

    fn compute_size (&mut self) -> &mut Self {
        let size = self.files.values().sum::<usize>();

        self.size = self.dirs.iter().fold(size, |acc, (_, dir)| {
            acc + dir.as_ref().borrow_mut().compute_size().size
        }); 

        self
    }

    fn sum<const THRESHOLD: usize>(&self) -> usize {
       let mut size = 0;
       if self.size <= THRESHOLD {
         size = self.size
       }

       self.dirs.iter().fold(size, |acc, (_, dir)| {
            acc + dir.as_ref().borrow().sum::<THRESHOLD>()
       })
    }
    
    fn find_deletion_candidate<const REQUIRED_SPACE: usize>(&self, unused_space: usize, mut candidate: usize) -> usize {
        if self.size + unused_space >= REQUIRED_SPACE && self.size < candidate {
          candidate = self.size;
        }

        self.dirs.iter().fold(candidate, |candidate, (_, dir)| {
            dir.as_ref().borrow().find_deletion_candidate::<REQUIRED_SPACE>(unused_space, candidate)
        })
    }
}

pub struct Day07;

impl Solution for Day07 {
    type Input = String;
    type Output1 = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_7.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output1 {
        self.parse(input)
            .as_ref()
            .borrow_mut()
            .compute_size()
            .sum::<100_000>()
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output2 {
        let fs = self.parse(input);
        let mut fs = fs.as_ref().borrow_mut();
        let fs = fs.compute_size();
        fs.find_deletion_candidate::<30_000_000>(70_000_000 - fs.size, fs.size)
    }
}

impl Day07 {
    fn parse(&self, commands: &[String]) -> Rc<RefCell<FileSystem>> {
        let mut fs = Rc::new(RefCell::new(FileSystem::new(None)));

        for command in commands {
            let mut command = command.split_whitespace();
            let op = command.next().unwrap();

            fs = match op {
                "$" => match command.next().unwrap() {
                    "cd" => fs
                        .as_ref()
                        .borrow_mut()
                        .cd_into(command.next().unwrap())
                        .unwrap(),
                    _ => fs,
                },
                "dir" => {
                    fs.as_ref().borrow_mut().add_dir(
                        command.next().unwrap().to_string(),
                        Rc::new(RefCell::new(FileSystem::new(Some(Rc::clone(&fs))))),
                    );
                    fs
                }
                size => {
                    fs.as_ref().borrow_mut().add_file(
                        command.next().unwrap().to_string(),
                        size.parse::<usize>().unwrap(),
                    );
                    fs
                }
            }
        }

        // rewind to root?
        self.find_root(fs)
    }

    fn find_root (&self, mut fs: Rc<RefCell<FileSystem>>) -> Rc<RefCell<FileSystem>> {
        while let Some (p) = Rc::clone(&fs).as_ref().borrow().parent.as_ref().map(Rc::clone) {
            fs = Rc::clone(&p);
        }

        fs
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day07};

    #[test]
    fn solution_is_correct() {
        Day07 {}.validate(1477771, 3579501);
    }
}
