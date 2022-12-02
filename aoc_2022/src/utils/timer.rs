

pub trait Timer {
    type Input;
    type Output;

    fn measure_pt_1(&self, input: &[Self::Input]) -> (Self::Output, f32);
    fn measure_pt_2(&self, input: &[Self::Input]) -> (Self::Output, f32);
}