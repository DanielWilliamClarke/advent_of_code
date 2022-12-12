use crate::utils::solution::Solution;
use std::{
    cmp::Ordering,
    collections::{BinaryHeap, HashSet}
};

#[derive(Hash, PartialEq, Eq, Clone, Copy)]
struct Coord {
    x: usize,
    y: usize,
}

impl Coord {
    fn new(x: usize, y: usize) -> Self {
        Coord { x, y }
    }
}

#[derive(PartialEq, Eq, Clone, Copy)]
struct Candidate {
    cost: usize,
    coord: Coord,
}

impl Candidate {
    fn new(cost: usize, coord: Coord) -> Self {
        Candidate { cost, coord }
    }
}

impl Ord for Candidate {
    fn cmp(&self, other: &Self) -> Ordering {
        other.cost.cmp(&self.cost)
    }
}

impl PartialOrd for Candidate {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

struct Grid {
    map: Vec<Vec<u8>>,
    start: Coord,
    end: Coord,
}

impl Grid {
    fn new(map: Vec<Vec<u8>>, start: Coord, end: Coord) -> Self {
        Grid { map, start, end }
    }

    fn dijkstra(
        &self, 
        arrival_criteria: impl Fn(&Grid, &Coord) -> bool, 
        candidate_criteria: impl Fn(u8, u8) -> bool
    ) -> usize {
        let mut priority_queue = BinaryHeap::new();
        let mut visited = HashSet::new();

        priority_queue.push(Candidate::new(0, self.start));
        visited.insert(self.start);

        while let Some(Candidate { cost, coord }) = priority_queue.pop() {
            if arrival_criteria(self, &coord) {
                return cost;
            }

            self.get_neighbors(&coord)
                .iter()
                .filter(|neighbor| {
                    candidate_criteria(self.map[coord.x][coord.y], self.map[neighbor.x][neighbor.y])
                })
                .filter(|neighbor| {
                    visited.insert(**neighbor)
                })
                .for_each(|neighbor| {
                    priority_queue.push(Candidate::new(cost + 1, *neighbor));
                });
        }

        usize::MAX
    }

    fn get_neighbors(&self, current: &Coord) -> Vec<Coord> {
        let mut space = Vec::new();

        // west
        if current.x > 0 {
            space.push(Coord::new(current.x - 1, current.y));
        }
        // easy
        if current.x < self.map.len() - 1 {
            space.push(Coord::new(current.x + 1, current.y));
        }
        // north
        if current.y > 0 {
            space.push(Coord::new(current.x, current.y - 1));
        }
        // south
        if current.y < self.map[0].len() - 1 {
            space.push(Coord::new(current.x, current.y + 1));
        }

        space
    }
}

pub struct Day12;

impl Solution for Day12 {
    type Input = String;
    type Output1 = usize;

    fn file_name(&self) -> &'static str {
        "src/days/input/day_12.txt"
    }

    fn pt_1(&self, input: &[Self::Input]) -> Self::Output1 {
        self.parse(input).dijkstra(
            |grid, coord| *coord == grid.end, 
            |current, neighbor| neighbor <= current || neighbor == current + 1
        )
    }

    fn pt_2(&self, input: &[Self::Input]) -> Self::Output2 {
        let mut grid = self.parse(input);
        // Monkey patch start as end
        grid.start = grid.end;
        // find closest lowest point
        grid.dijkstra(
            |grid, coord| grid.map[coord.x][coord.y] == 0,
            |current, neighbor| neighbor >= current || neighbor == current - 1
        )
    }
}

impl Day12 {
    fn parse(&self, input: &[String]) -> Grid {
        let mut start = Coord::new(0, 0);
        let mut end = Coord::new(0, 0);

        let nodes = input
            .iter()
            .enumerate()
            .map(|(x, row)| {
                row.char_indices()
                    .map(|(y, point)| {
                        let letter = match point {
                            'S' => {
                                start = Coord::new(x, y);
                                'a'
                            }
                            'E' => {
                                end = Coord::new(x, y);
                                'z'
                            }
                            point => point,
                        };

                        letter as u8 - b'a'
                    })
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();

        Grid::new(nodes.clone(), start, end)
    }
}

#[cfg(test)]
mod tests {
    use crate::{utils::validator::Validator, Day12};

    #[test]
    fn solution_is_correct() {
        Day12 {}.validate(456, 454);
    }
}
