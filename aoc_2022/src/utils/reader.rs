// src/utils/reader.rs

pub trait Reader {
    type Data;

    fn read_input(&self, file_name: &str) -> Vec<Self::Data>;
}