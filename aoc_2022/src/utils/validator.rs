// src/utils/test_utils.rs

#[cfg(test)]
pub mod validator {
    pub trait Validator {
        type Output;
    
        fn validate(&self, file_name: &str, expectations: (Self::Output, Self::Output));
    }
}

