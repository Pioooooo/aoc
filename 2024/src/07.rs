use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let lines = contents.trim().lines().collect::<Vec<&str>>();

    let sum1 = lines
        .iter()
        .map(|line| {
            let parts: Vec<&str> = line.split(": ").collect();
            let value: i64 = parts[0].parse().unwrap();
            let operands: Vec<i64> = parts[1]
                .split_whitespace()
                .map(|s| s.parse().unwrap())
                .collect();

            let n = operands.len();
            let num_combinations = 1 << (n - 1);
            for ops in 0..num_combinations {
                let mut result = operands[0];
                for i in 0..(n - 1) {
                    if (ops >> i) & 1 == 1 {
                        result += operands[i + 1];
                    } else {
                        result *= operands[i + 1];
                    }
                }
                if result == value {
                    return value;
                }
            }
            0
        })
        .sum::<i64>();
    println!("P1: {}", sum1);
    let sum2 = lines
        .iter()
        .map(|line| {
            let parts: Vec<&str> = line.split(": ").collect();
            let value: i64 = parts[0].parse().unwrap();
            let operands: Vec<i64> = parts[1]
                .split_whitespace()
                .map(|s| s.parse().unwrap())
                .collect();

            let n = operands.len();
            let num_combinations = 3_i64.pow((n - 1) as u32);
            for ops in 0..num_combinations {
                let mut result = operands[0];
                let mut j = ops;
                for i in 0..(n - 1) {
                    let op = j % 3;
                    j /= 3;
                    if op == 0 {
                        result += operands[i + 1];
                    } else if op == 1 {
                        result *= operands[i + 1];
                    } else {
                        result =
                            result * 10_i64.pow(operands[i + 1].ilog10() + 1) + operands[i + 1];
                    }
                }
                if result == value {
                    return value;
                }
            }
            0
        })
        .sum::<i64>();
    println!("P2: {}", sum2);
}
