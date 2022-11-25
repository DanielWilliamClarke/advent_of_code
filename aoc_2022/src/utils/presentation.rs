// src/solution/presentation.rs

pub trait Presentation {
    fn print_results(&self, file_name: &str);

    fn print_div(&self) {
        println!("🎄{:=<1$}🎄", "", 70);
    }
}
