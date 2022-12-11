// src/utils/test_utils.rs

#[cfg(test)]
pub trait Validator {
    type Output1;
    type Output2 = Self::Output1;

    fn validate(&self, pt1: Self::Output1, pt2: Self::Output2);
} 

