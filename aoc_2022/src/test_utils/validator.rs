// src/utils/test_utils.rs

#[cfg(test)]
pub mod validator {
    use std::fmt::Debug;
    use std::cmp::PartialEq;

    pub fn validate_solution<T>(expectations: Vec<(T, T)>)
    where 
        T: Debug + PartialEq 
    {
        expectations
            .iter()
            .for_each(|test| assert_eq!(test.0, test.1))
    }
}
