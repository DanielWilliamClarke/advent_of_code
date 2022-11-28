// src/utils/presentation.rs

pub trait Printer {
    fn print(&self, file_name: &str);

    fn div(&self) {
        println!("🎄{:=<1$}🎄", "", 70);
    }
}
