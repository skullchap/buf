use std::time::Instant;

fn main() {
    let iterations: usize = 1_000_000_000;
    let mut vec: Vec<usize> = Vec::new();

    let start = Instant::now();
    for i in 0..iterations {
        vec.push(i);
    }
    let duration = start.elapsed();

    println!("Rust Vec time: {:.2?} seconds", duration);
}
