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

        for index in 1..grid.len() - 1 {
            for jndex in 1..grid[index].len() - 1 {
                let tree = grid[index][jndex];

                visible += (
                    self.look(0..=index-1, |north| grid[north][jndex] >= tree) || 
                    self.look(index+1..grid.len(), |south| grid[south][jndex] >= tree) ||
                    self.look(0..=jndex-1, |west| grid[index][west] >= tree) ||
                    self.look(jndex+1..grid[index].len(), |east| grid[index][east] >= tree)
                ) as usize;
            }
        }

        visible
    }

    fn calculate_scenic_score(&self, grid: &Vec<Vec<usize>>) -> usize {
        let mut highest_score = 0;

        for index in 1..grid.len() - 1 {
            for jndex in 1..grid[index].len() - 1 {
                let tree = grid[index][jndex];

                //look north
                let score = 
                    self.score((0..=index-1).rev(), |north| grid[north][jndex] >= tree) *
                    self.score(index+1..grid.len(), |south| grid[south][jndex] >= tree) *
                    self.score((0..=jndex-1).rev(), |west| grid[index][west] >= tree) *
                    self.score(jndex+1..grid[index].len(), |east| grid[index][east] >= tree);

                // let score = score_north * score_south * score_west * score_east;
                if score > highest_score {
                    highest_score = score;
                }
            }
        }

        highest_score
    }

    fn look<T: Iterator>(&self, range: T, criteria: impl Fn(<T as Iterator>::Item) -> bool) -> bool {
        for dir in range { 
            if criteria(dir) {
                return false;
            }
        }

        true
    }

    fn score<T: Iterator>(&self, range: T, criteria: impl Fn(<T as Iterator>::Item) -> bool) -> usize {
        let mut score = 0;

        for dir in range { 
            score += 1;
            if criteria(dir) {
                break;  
            }
        }

        score
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
