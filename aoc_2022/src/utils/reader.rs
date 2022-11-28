// src/utils/reader.rs

pub trait Reader {
    type Data;

    fn read(&self, file_name: &str) -> Vec<Self::Data>;
}