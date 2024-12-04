use regex::Regex;
use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let re = Regex::new(r"do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\)").unwrap();
    let mut enabled = true;
    let mut sum1 = 0;
    let mut sum2 = 0;

    for cap in re.captures_iter(&contents) {
        let s = &cap[0];
        if s == "do()" {
            enabled = true;
        } else if s == "don't()" {
            enabled = false;
        } else {
            let num1: i32 = cap[1].parse().unwrap();
            let num2: i32 = cap[2].parse().unwrap();
            sum1 += num1 * num2;
            if enabled {
                sum2 += num1 * num2;
            }
        }
    }
    println!("P1: {}", sum1);
    println!("P2: {}", sum2);
}
