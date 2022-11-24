use crate::common::Solution;

const CHANNELS: usize = 9;
const SPAWN: usize = 0;
const RESET: usize = 6;
const FRESH: usize = 8;

pub struct Day06;

impl Solution<String, usize> for Day06 {
    fn pt_1(&self, input: &[String]) -> usize {
        self.simulate(&self.parse(input), 80)
    }

    fn pt_2(&self, input: &[String]) -> usize {
        self.simulate(&self.parse(input), 256)
    }
}

impl Day06 {
    pub fn new() -> Day06 {
        Day06 {}
    }

    fn parse(&self, input: &[String]) -> Vec<usize> {
        input
            .first()
            .unwrap()
            .split(',')
            .map(|number| number.parse().unwrap())
            .collect()
    }

    fn simulate(&self, input: &[usize], iterations: usize) -> usize {
        let mut dict = self.list_to_dict(input);
        (0..iterations).for_each(|_| dict = self.one_pass(&dict));
        dict.iter().sum()
    }
    
    fn list_to_dict(&self,  input: &[usize]) -> Vec<usize> {
        input
            .iter()
            .fold(self.make_dict(), 
                |mut dict, timer| {
                    dict[*timer] += 1;
                    dict
                })
    }

    fn one_pass(&self, dict: &[usize]) -> Vec<usize> {
        let mut snapshot = self.make_dict();

        dict.iter()
            .enumerate()
            .for_each(|(time, _)| match time == SPAWN {
                true => {
                    snapshot[RESET] += dict[0];
                    snapshot[FRESH] += dict[0];
                }
                false => snapshot[time - 1] += dict[time],
            });

        snapshot
    }

    fn make_dict(&self) -> Vec<usize>{
        vec![0usize; CHANNELS]
    }
}

#[cfg(test)]
mod tests {
    use crate::{common::Solution, day_06::solution::Day06};

    #[test]
    fn solution_is_correct() {
        let day = Day06::new();
        let input = day.read_input("src/day_06/input.txt");
        vec![
            (day.pt_1(&input), 390011),
            (day.pt_2(&input), 1746710169834),
        ]
        .iter()
        .for_each(|test| assert_eq!(test.0, test.1))
    }
}
