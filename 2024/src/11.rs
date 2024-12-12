use std::fs;
use std::collections::HashMap;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let input = contents
        .trim()
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect::<Vec<i64>>();

    let mut stones = HashMap::new();
    for stone in input {
        *stones.entry(stone).or_insert(0) += 1;
    }

    let blink = |stones: HashMap<i64, usize>| -> HashMap<i64, usize> {
        let mut new_stones = HashMap::new();
        for (stone, count) in stones {
            if stone == 0 {
                *new_stones.entry(1).or_insert(0) += count;
            } else {
                let stone_str = stone.to_string();
                let num_digits = stone_str.len();
                if num_digits % 2 == 0 {
                    let mid = num_digits / 2;
                    let left_part = &stone_str[..mid];
                    let right_part = &stone_str[mid..];
                    let left_num = left_part.parse::<i64>().unwrap();
                    let right_num = right_part.parse::<i64>().unwrap();
                    *new_stones.entry(left_num).or_insert(0) += count;
                    *new_stones.entry(right_num).or_insert(0) += count;
                } else {
                    *new_stones.entry(stone * 2024).or_insert(0) += count;
                }
            }
        }
        new_stones
    };

    for _ in 0..25 {
        stones = blink(stones);
    }

    let total_stones: usize = stones.values().sum();
    println!("P1 {}", total_stones);

    for _ in 25..75 {
        stones = blink(stones);
    }

    let total_stones: usize = stones.values().sum();
    println!("P2 {}", total_stones);
}
