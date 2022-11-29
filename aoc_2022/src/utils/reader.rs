// src/utils/reader.rs

pub trait Reader {
    type Data;

    fn read(&self) -> Vec<Self::Data>;
}