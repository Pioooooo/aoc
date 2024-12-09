use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let dat = contents
        .trim()
        .chars()
        .map(|c| c.to_digit(10).unwrap() as usize)
        .collect::<Vec<usize>>();
    let len = dat.len() / 2;
    let mut sum = 0;
    let mut i = 0;
    let mut tail = len;
    let mut tail_len = dat[2 * tail];
    let mut pos = 0;
    let mut sum_region = |i: usize, length: usize| {
        sum += i * length * (length + 2 * pos - 1) / 2;
        pos += length;
    };
    loop {
        if i == tail {
            sum_region(i, tail_len);
            break;
        }
        sum_region(i, dat[2 * i]);
        let mut space = dat[2 * i + 1];
        while space > 0 {
            if i == tail {
                break;
            }
            if space <= tail_len {
                sum_region(tail, space);
                tail_len -= space;
                break;
            }
            sum_region(tail, tail_len);
            space -= tail_len;
            tail -= 1;
            tail_len = dat[2 * tail];
        }
        i += 1;
    }
    println!("P1: {}", sum);

    let mut files = Vec::new();
    let mut spaces = Vec::new();
    let mut position = 0usize;
    let len = dat.len();
    for (i, &length) in dat.iter().enumerate() {
        if i % 2 == 0 {
            files.push((position, length));
        } else {
            spaces.push((position, length));
        }
        position += length;
    }

    files.reverse();

    let mut total = 0;
    let mut sum_region2 = |i: usize, pos: usize, length: usize| {
        total += i * length * (length + 2 * pos - 1) / 2;
    };

    for (fid, &(pos, length)) in files.iter().enumerate() {
        let mut found_space = false;
        for space in &mut spaces {
            if space.1 >= length {
                sum_region2(len / 2 - fid, space.0, length);
                space.0 += length;
                space.1 -= length;
                found_space = true;
                break;
            }
        }
        if !found_space {
            sum_region2(len / 2 - fid, pos, length);
        }
        spaces.pop();
    }

    println!("P2: {}", total);
}
