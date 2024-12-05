use core::panic;
use std::collections::{HashMap, HashSet};
use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let sections: Vec<&str> = contents.trim().split("\n\n").collect();

    let rules: Vec<(i32, i32)> = sections[0]
        .lines()
        .map(|line| {
            let pair: Vec<&str> = line.split('|').collect();
            (pair[0].parse().unwrap(), pair[1].parse().unwrap())
        })
        .collect();

    let updates: Vec<Vec<i32>> = sections[1]
        .lines()
        .map(|line| line.split(',').map(|s| s.parse().unwrap()).collect())
        .collect();

    let mut sum1 = 0;
    let mut sum2 = 0;
    for update in updates.iter() {
        let mut valid = true;
        for rule in rules.iter() {
            let pos0 = update.iter().position(|&x| x == rule.0);
            let pos1 = update.iter().position(|&x| x == rule.1);
            if pos0.is_none() || pos1.is_none() {
                continue;
            }
            if pos1 < pos0 {
                valid = false;
                break;
            }
        }
        if valid {
            sum1 += update[update.len() / 2];
        } else {
            let mut graph: HashMap<i32, Vec<i32>> = HashMap::new();
            let mut in_degree: HashMap<i32, i32> = HashMap::new();
            let elements: HashSet<i32> = update.iter().cloned().collect();

            for &node in elements.iter() {
                graph.entry(node).or_insert(Vec::new());
                in_degree.entry(node).or_insert(0);
            }

            for &(a, b) in rules.iter() {
                if elements.contains(&a) && elements.contains(&b) {
                    graph.get_mut(&a).unwrap().push(b);
                    *in_degree.get_mut(&b).unwrap() += 1;
                }
            }

            let mut queue: Vec<i32> = in_degree
                .iter()
                .filter(|&(_, &deg)| deg == 0)
                .map(|(&node, _)| node)
                .collect();
            let mut sorted = Vec::new();

            while let Some(node) = queue.pop() {
                sorted.push(node);
                if let Some(neighbors) = graph.get(&node) {
                    for &neighbor in neighbors {
                        *in_degree.get_mut(&neighbor).unwrap() -= 1;
                        if in_degree[&neighbor] == 0 {
                            queue.push(neighbor);
                        }
                    }
                }
            }
            if sorted.len() != elements.len() {
                panic!("Cannot sort the graph");
            }

            sum2 += sorted[sorted.len() / 2];
        }
    }
    println!("P1: {}", sum1);
    println!("P2: {}", sum2);
}
