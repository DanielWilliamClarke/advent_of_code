// src/utils/test_utils.rs

#[cfg(test)]
pub mod validator {
    pub trait Validator {
        type Output;
    
        fn validate(&self, pt1: Self::Output, pt2: Self::Output);
    }
}

