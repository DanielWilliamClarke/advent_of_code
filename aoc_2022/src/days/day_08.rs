// src/days/day_00/solution.rs
use crate::utils::solution::Solution;

pub struct Day08;

impl Solution for Day08 {
    type Input = String;
    type Output = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_8.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output {
        let grid = self.parse(input);

        self.count_perimeter(&grid) + self.count_visible(&grid)
    }

    fn pt_2(&self, _: &[Self::Input]) -> Self::Output {
        0
    }
}

impl Day08 {
    fn parse(&self, input: &[String]) -> Vec<Vec<usize>> {
        input
            .iter()
            .map(|row| {
                row.chars()
                    .map(|tree| tree.to_digit(10).unwrap() as usize)
                    .collect()
            })
            .collect()
    }

    fn count_perimeter(&self, grid: &Vec<Vec<usize>>) -> usize {
        (grid[0].len() * 2) + (grid.len() * 2) - 4
    }

    fn count_visible(&self, grid: &Vec<Vec<usize>>) -> usize {
        let mut visible = 0;

        for i in 1..grid.len() - 1 {
            for j in 1..grid[i].len() - 1 {
                let tree = grid[i][j];

                //look north
                let mut is_visible = true;
                for n in 0..i {
                    if n != i && grid[n][j] >= tree {
                        is_visible = false;
                        break;
                    }
                }
                if is_visible {
                    visible += 1;
                    continue;
                }

                // look south
                let mut is_visible = true;
                for s in i..grid.len() {
                    if s != i && grid[s][j] >= tree {
                        is_visible = false;
                        break;
                    }
                }
                if is_visible {
                    visible += 1;
                    continue;
                }

                // look west
                let mut is_visible = true;
                for w in 0..j {
                    if w != j && grid[i][w] >= tree {
                        is_visible = false;
                        break;
                    }
                }
                if is_visible {
                    visible += 1;
                    continue;
                }

                // look east
                let mut is_visible = true;
                for e in j..grid[i].len() {
                    if e != j && grid[i][e] >= tree {
                        is_visible = false;
                        break;
                    }
                }
                if is_visible {
                    visible += 1;
                    continue;
                }
            }
        }

        visible
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day08};

    #[test]
    fn solution_is_correct() {
        Day08 {}.validate(1538, 0);
    }
}
