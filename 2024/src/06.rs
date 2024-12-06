use std::collections::HashSet;
use std::fs;

const FILE_PATH: &str = "in";

fn is_in_loop(grid: &Vec<Vec<char>>, start_pos: (usize, usize), direction: usize) -> bool {
    let directions = [(-1, 0), (0, 1), (1, 0), (0, -1)];
    let mut visited = HashSet::new();
    let mut current_pos = start_pos;
    let mut dir = direction;

    loop {
        if !visited.insert((current_pos, dir)) {
            return true;
        }
        let (x, y) = current_pos;
        let (dx, dy) = directions[dir];
        let next_pos = (x.wrapping_add(dx as usize), y.wrapping_add(dy as usize));

        if next_pos.0 >= grid.len() || next_pos.1 >= grid[0].len() {
            break;
        }
        if grid[next_pos.0][next_pos.1] == '#' {
            dir = (dir + 1) % 4;
        } else {
            current_pos = next_pos;
        }
    }
    false
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

    let mut found = None;
    grid.iter().enumerate().any(|(i, line)| {
        line.iter().enumerate().any(|(j, &c)| {
            if c == '^' {
                found = Some((i, j));
                true
            } else {
                false
            }
        })
    });

    let directions = [(-1, 0), (0, 1), (1, 0), (0, -1)];

    let mut direction = 0;
    let start_pos = found.unwrap();
    let mut current_pos = start_pos;

    let mut visited = HashSet::new();
    visited.insert(current_pos);

    loop {
        let (x, y) = current_pos;
        let (dx, dy) = directions[direction];
        let next_pos = (x.wrapping_add(dx as usize), y.wrapping_add(dy as usize));

        if next_pos.0 >= row || next_pos.1 >= col {
            break;
        }
        if grid[next_pos.0][next_pos.1] == '#' {
            direction = (direction + 1) % 4;
        } else {
            current_pos = next_pos;
            visited.insert(current_pos);
        }
    }

    println!("P1: {}", visited.len());

    let mut possible_positions = 0;

    for i in 0..row {
        for j in 0..col {
            if grid[i][j] == '.' {
                let mut new_grid = grid.clone();
                new_grid[i][j] = '#';
                if is_in_loop(&new_grid, start_pos, 0) {
                    possible_positions += 1;
                }
            }
        }
    }

    println!("P2: {:?}", possible_positions);
}
