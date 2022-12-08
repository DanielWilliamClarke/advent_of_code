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

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output {
        let grid = self.parse(input);
        self.calculate_scenic_score(&grid)
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

    fn calculate_scenic_score(&self, grid: &Vec<Vec<usize>>) -> usize {
        let mut highest_score = 0;

        for i in 1..grid.len() - 1 {
            for j in 1..grid[i].len() - 1 {
                let tree = grid[i][j];

                //look north
                let mut score_north = 0;
                for n in (0..i).rev() {
                    if n != i {
                        score_north += 1;
                        if grid[n][j] >= tree {
                            break;
                        }
                    }
                }

                // look south
                let mut score_south = 0;
                for s in i..grid.len() {
                    if s != i {
                        score_south += 1;
                        if grid[s][j] >= tree {
                            break;
                        }
                    }
                }     

                // look west
                let mut score_west = 0;
                for w in (0..j).rev() {
                    if w != j {
                        score_west += 1;
                        if grid[i][w] >= tree {
                            break;
                        }
                    }
                }

                // look east
                let mut score_east = 0;
                for e in j..grid[i].len() {
                    if e != j {
                        score_east += 1;
                        if grid[i][e] >= tree {
                            break;
                        }
                    }
                }

                let score = score_north * score_south * score_west * score_east;
                if score > highest_score {
                    highest_score = score;
                }
            }
        }

        highest_score
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day08};

    #[test]
    fn solution_is_correct() {
        Day08 {}.validate(1538, 496125);
    }
}
