// src/utils/presentation.rs

use std::{fmt::{Display, Debug}, str::FromStr, any::type_name};

use super::{solution::Solution, reader::Reader};

pub struct Printer<S>(pub S);

impl<S: Solution> Display for Printer<S>
where
    <S as Solution>::Input: FromStr,
    <<S as Solution>::Input as FromStr>::Err: Debug,
    <S as Solution>::Output: Display,
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;
        writeln!(f, "     🎅 Running Advent Of Code 2022: {} 🎅", type_name::<S>())?;
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;
        let input = self.0.read();
        writeln!(f, "     🥁 Part 1 result: {}", self.0.pt_1(&input))?;
        writeln!(f, "     🥁 Part 2 result: {}", self.0.pt_2(&input))?;
        writeln!(f, "🎄{:=<1$}🎄", "", 70)?;

        Ok(())
    }
}