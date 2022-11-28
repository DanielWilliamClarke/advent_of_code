// src/utils/presentation.rs

pub trait Printer {
    fn print_results(&self, file_name: &str);

    fn print_div(&self) {
        println!("🎄{:=<1$}🎄", "", 70);
    }
}
