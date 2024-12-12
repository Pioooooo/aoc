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

    let mut visited = vec![vec![false; col]; row];
    let mut total_price_p1 = 0;
    let mut total_price_p2 = 0;

    for i in 0..row {
        for j in 0..col {
            if !visited[i][j] {
                let (area, perimeter, corners) = dfs(i, j, &grid, &mut visited, grid[i][j]);
                total_price_p1 += area * perimeter;
                total_price_p2 += area * corners;
            }
        }
    }

    println!("P1: {}", total_price_p1);
    println!("P2: {}", total_price_p2);
}

fn dfs(
    start_x: usize,
    start_y: usize,
    grid: &Vec<Vec<char>>,
    visited: &mut Vec<Vec<bool>>,
    region_char: char,
) -> (usize, usize, usize) {
    let mut area = 0;
    let mut perimeter = 0;
    let mut corners = 0;
    let row = grid.len();
    let col = grid[0].len();
    let directions = [(-1, 0), (0, 1), (1, 0), (0, -1)];

    let mut stack = vec![(start_x, start_y)];
    visited[start_x][start_y] = true;

    while let Some((x, y)) = stack.pop() {
        area += 1;
        for (dx, dy) in directions.iter() {
            let nx = x as isize + dx;
            let ny = y as isize + dy;

            if nx >= 0 && nx < row as isize && ny >= 0 && ny < col as isize {
                let nx = nx as usize;
                let ny = ny as usize;
                if grid[nx][ny] == region_char {
                    if !visited[nx][ny] {
                        visited[nx][ny] = true;
                        stack.push((nx, ny));
                    }
                } else {
                    perimeter += 1;
                }
            } else {
                perimeter += 1;
            }
        }
        let get = |x: isize, y: isize| -> char {
            if x >= 0 && x < row as isize && y >= 0 && y < col as isize {
                grid[x as usize][y as usize]
            } else {
                0 as char
            }
        };
        for (dx, dy) in [(-1, -1), (-1, 1), (1, -1), (1, 1)] {
            let a = region_char;
            let b = get(x as isize + dx, y as isize);
            let c = get(x as isize, y as isize + dy);
            let d = get(x as isize + dx, y as isize + dy);
            if b != a && c != a || b == a && c == a && d != a {
                corners += 1;
            }
        }
    }

    (area, perimeter, corners)
}
