use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let grid: Vec<Vec<char>> = contents
        .trim()
        .split('\n')
        .map(|line| line.chars().collect())
        .collect();
    let col = grid[0].len();
    let row = grid.len();
    let mut cnt1 = 0;
    let mut cnt2 = 0;
    let directions = [
        (0, 1),
        (1, 0),
        (0, -1),
        (-1, 0),
        (1, 1),
        (1, -1),
        (-1, -1),
        (-1, 1),
    ];
    for i in 0..row {
        for j in 0..col {
            for &(dx, dy) in &directions {
                if check(&grid, i as i32, j as i32, dx, dy, "XMAS") {
                    cnt1 += 1;
                }
            }
            if check_x_shape(&grid, i, j, "MAS") {
                cnt2 += 1;
            }
        }
    }
    println!("P1: {}", cnt1);
    println!("P2: {}", cnt2);
}

fn check(grid: &Vec<Vec<char>>, x: i32, y: i32, dx: i32, dy: i32, word: &str) -> bool {
    let mut x = x;
    let mut y = y;
    for ch in word.chars() {
        if x < 0 || x >= grid.len() as i32 || y < 0 || y >= grid[0].len() as i32 {
            return false;
        }
        if grid[x as usize][y as usize] != ch {
            return false;
        }
        x += dx;
        y += dy;
    }
    true
}

fn check_x_shape(grid: &Vec<Vec<char>>, x: usize, y: usize, word: &str) -> bool {
    let directions = [(1, 1), (1, -1), (-1, 1), (-1, -1)];
    let len = word.len() as i32;
    let mut cnt = 0;
    for &(dx, dy) in &directions {
        let mut found = true;
        for (i, ch) in word.chars().enumerate() {
            let nx = x as i32 + (i as i32 - len / 2) * dx;
            let ny = y as i32 + (i as i32 - len / 2) * dy;
            if nx < 0
                || nx >= grid.len() as i32
                || ny < 0
                || ny >= grid[0].len() as i32
                || grid[nx as usize][ny as usize] != ch
            {
                found = false;
                break;
            }
        }
        if found {
            cnt += 1;
            if cnt == 2 {
                return true;
            }
        }
    }
    false
}
