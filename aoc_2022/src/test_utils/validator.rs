// src/utils/test_utils.rs

#[cfg(test)]
pub mod validator {
    use std::cmp::PartialEq;
    use std::fmt::Debug;

    use crate::utils::reader::Reader;
    use crate::utils::solution::Solution;

    pub fn validate_solution<S, O>(solution: S, file_name: &str, expectations: (O, O))
    where
        S: Solution<Output = O> + Reader<Data = <S as Solution>::Input>,
        O: Debug + PartialEq,
    {
        let input = solution.read_input(file_name);
        let results = vec![
            (solution.pt_1(&input), expectations.0),
            (solution.pt_2(&input), expectations.1),
        ];
        results.iter().for_each(|test| assert_eq!(test.0, test.1))
    }
}
