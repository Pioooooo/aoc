use std::collections::{HashMap, HashSet};
use std::fs;

const FILE_PATH: &str = "in";

// 添加计算最大公约数的函数
fn gcd(a: isize, b: isize) -> isize {
    if b == 0 {
        a.abs()
    } else {
        gcd(b, a % b)
    }
}

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let grid: Vec<Vec<char>> = contents
        .trim()
        .split('\n')
        .map(|line| line.chars().collect())
        .collect();
    let col = grid[0].len();
    let row = grid.len();
    let mut antennas = HashMap::new();
    grid.iter().enumerate().for_each(|(i, l)| {
        l.iter().enumerate().for_each(|(j, c)| {
            if *c != '.' {
                antennas
                    .entry(*c)
                    .or_insert_with(HashSet::new)
                    .insert((i, j));
            }
        })
    });

    let mut pos_set = HashSet::new();
    antennas.iter().for_each(|(_, pos)| {
        for &m in pos {
            for &n in pos {
                if n == m {
                    continue;
                }
                let pos = (
                    m.0.wrapping_mul(2).wrapping_sub(n.0),
                    m.1.wrapping_mul(2).wrapping_sub(n.1),
                );
                if pos.0 < row && pos.1 < col {
                    pos_set.insert(pos);
                }
            }
        }
    });
    println!("P1: {}", pos_set.len());

    let mut pos_set2 = HashSet::new();
    antennas.iter().for_each(|(_, pos)| {
        for &m in pos {
            for &n in pos {
                if n == m {
                    continue;
                }
                let delta_x = n.0 as isize - m.0 as isize;
                let delta_y = n.1 as isize - m.1 as isize;
                let step_gcd = gcd(delta_x, delta_y);
                let dir_x = delta_x / step_gcd;
                let dir_y = delta_y / step_gcd;
                for &dir in &[ (dir_x, dir_y), (-dir_x, -dir_y) ] {
                    let mut current = (n.0 as isize + dir.0, n.1 as isize + dir.1);
                    while current.0 >= 0 && current.0 < row as isize &&
                          current.1 >= 0 && current.1 < col as isize {
                        pos_set2.insert((current.0 as usize, current.1 as usize));
                        current = (current.0 + dir.0, current.1 + dir.1);
                    }
                }
            }
        }
    });
    println!("P2: {}", pos_set2.len());
}
