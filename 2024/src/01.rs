use std::collections::HashMap;
use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let lines = contents.split('\n').collect::<Vec<&str>>();

    let (mut first_column, mut second_column): (Vec<i32>, Vec<i32>) = lines
        .iter()
        .filter_map(|line| {
            let nums: Vec<&str> = line.split_whitespace().collect();
            if nums.len() == 2 {
                Some((
                    nums[0].parse::<i32>().unwrap(),
                    nums[1].parse::<i32>().unwrap(),
                ))
            } else {
                None
            }
        })
        .unzip();

    first_column.sort();
    second_column.sort();

    let distance: i32 = first_column
        .iter()
        .zip(second_column.iter())
        .map(|(a, b)| (a - b).abs())
        .sum();

    println!("P1: {:?}", distance);

    let first_column_counts = first_column.iter().fold(HashMap::new(), |mut acc, &num| {
        *acc.entry(num).or_insert(0) += 1;
        acc
    });

    let second_column_counts = second_column.iter().fold(HashMap::new(), |mut acc, &num| {
        *acc.entry(num).or_insert(0) += 1;
        acc
    });

    let product_sum: i32 = first_column_counts
        .iter()
        .filter_map(|(&num, &count)| {
            second_column_counts
                .get(&num)
                .map(|&second_count| num * count * second_count)
        })
        .sum();

    println!("P2: {:?}", product_sum);
}
