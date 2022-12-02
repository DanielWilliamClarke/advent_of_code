// src/utils/presentation.rs

use std::{fmt::{Display, Debug}, str::FromStr, any::type_name};

use super::{solution::Solution, reader::Reader};
pub struct Printer<S>(pub S);

impl<S: Solution> Display for Printer<S>
where
    <S as Solution>::Input: FromStr + Display,
    <<S as Solution>::Input as FromStr>::Err: Debug,
    <S as Solution>::Output: Display + Debug,
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;
        writeln!(f, "     🎅 Running Advent Of Code 2022: {} 🎅", type_name::<S>())?;
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;
        let input = self.0.read();
        let (result, timing) = self.0.measure_pt_1(&input);
        writeln!(f, "     🥁 Part 1 - result: {} timing: {}s", result, timing)?;
        let (result, timing) = self.0.measure_pt_2(&input);
        writeln!(f, "     🥁 Part 2 - result: {} timing: {}s", result, timing)?;
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;

        Ok(())
    }
}

