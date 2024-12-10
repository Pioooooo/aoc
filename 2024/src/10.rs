use std::collections::{HashMap, HashSet, VecDeque};
use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let grid: Vec<Vec<u32>> = contents
        .trim()
        .split('\n')
        .map(|line| line.chars().map(|c| c.to_digit(10).unwrap()).collect())
        .collect();
    let col = grid[0].len();
    let row = grid.len();

    let mut total = 0;
    for i in 0..row {
        for j in 0..col {
            if grid[i][j] == 0 {
                total += count_reachable_nines(&grid, i, j, row, col);
            }
        }
    }
    println!("P1: {}", total);

    let mut total_paths = 0;
    for i in 0..row {
        for j in 0..col {
            if grid[i][j] == 0 {
                let paths = count_paths(&grid, i, j, row, col);
                total_paths += paths;
            }
        }
    }
    println!("P2: {}", total_paths);
}

fn count_reachable_nines(
    grid: &Vec<Vec<u32>>,
    start_i: usize,
    start_j: usize,
    row: usize,
    col: usize,
) -> usize {
    let directions = [(-1, 0), (0, 1), (1, 0), (0, -1)];
    let mut visited = HashSet::new();
    let mut queue = VecDeque::new();
    let mut reachable_nines = HashSet::new();
    queue.push_back((start_i, start_j, grid[start_i][start_j]));
    visited.insert((start_i, start_j));
    while let Some((i, j, value)) = queue.pop_front() {
        if grid[i][j] == 9 {
            reachable_nines.insert((i, j));
        }
        for &(dx, dy) in &directions {
            let new_i = i as isize + dx;
            let new_j = j as isize + dy;
            if new_i >= 0 && new_i < row as isize && new_j >= 0 && new_j < col as isize {
                let new_i = new_i as usize;
                let new_j = new_j as usize;
                if !visited.contains(&(new_i, new_j)) && grid[new_i][new_j] == value + 1 {
                    visited.insert((new_i, new_j));
                    queue.push_back((new_i, new_j, grid[new_i][new_j]));
                }
            }
        }
    }
    reachable_nines.len()
}

// 添加计算路径数的函数
fn count_paths(grid: &Vec<Vec<u32>>, i: usize, j: usize, row: usize, col: usize) -> usize {
    let mut memo = HashMap::new();
    dfs(grid, i, j, row, col, &mut memo)
}

fn dfs(
    grid: &Vec<Vec<u32>>,
    i: usize,
    j: usize,
    row: usize,
    col: usize,
    memo: &mut HashMap<(usize, usize), usize>,
) -> usize {
    if grid[i][j] == 9 {
        return 1;
    }
    if let Some(&count) = memo.get(&(i, j)) {
        return count;
    }
    let directions = [(-1, 0), (0, 1), (1, 0), (0, -1)];
    let mut total = 0;
    for &(dx, dy) in &directions {
        let new_i = i as isize + dx;
        let new_j = j as isize + dy;
        if new_i >= 0 && new_i < row as isize && new_j >= 0 && new_j < col as isize {
            let new_i = new_i as usize;
            let new_j = new_j as usize;
            if grid[new_i][new_j] == grid[i][j] + 1 {
                total += dfs(grid, new_i, new_j, row, col, memo);
            }
        }
    }
    memo.insert((i, j), total);
    total
}
