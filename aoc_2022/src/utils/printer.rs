// src/utils/presentation.rs

use std::{fmt::{Display, Debug}, str::FromStr, any::type_name, time::Instant};

use super::{solution::Solution, reader::Reader, timer::Timer};

pub struct Printer<S>(pub S);

impl<S: Solution> Timer for Printer<S>
where  
    <S as Solution>::Output: Debug,
{
    type Input = <S as Solution>::Input;
    type Output = <S as Solution>::Output;

    fn measure_pt_1(&self, input: &[Self::Input]) -> (Self::Output, f32) {
        let now = Instant::now();
        (self.0.pt_1(&input), now.elapsed().as_secs_f32())
    }

    fn measure_pt_2(&self, input: &[Self::Input]) -> (Self::Output, f32) {
        let now = Instant::now();
        (self.0.pt_2(&input), now.elapsed().as_secs_f32())
    }
}

impl<S: Solution> Display for Printer<S>
where
    <S as Solution>::Input: FromStr + Display + Clone + 'static,
    <<S as Solution>::Input as FromStr>::Err: Debug,
    <S as Solution>::Output: Display + Debug,
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;
        writeln!(f, "     🎅 Running Advent Of Code 2022: {} 🎅", type_name::<S>())?;
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;
        let input = self.0.read();
        let (result, timing) = self.measure_pt_1(&input);
        writeln!(f, "     🥁 Part 1 - result: {} timing: {}s", result, timing)?;
        let (result, timing) = self.measure_pt_2(&input);
        writeln!(f, "     🥁 Part 2 - result: {} timing: {}s", result, timing)?;
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;

        Ok(())
    }
}

