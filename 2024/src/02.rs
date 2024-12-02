use std::fs;

const FILE_PATH: &str = "in";

fn main() {
    let contents = fs::read_to_string(FILE_PATH).expect("Should have been able to read the file");
    let lines = contents
        .trim()
        .split('\n')
        .filter_map(|s| {
            s.split_whitespace()
                .map(|x| x.parse())
                .collect::<Result<Vec<i32>, _>>()
                .ok()
        })
        .collect::<Vec<Vec<i32>>>();
    let safe_cnt = lines
        .iter()
        .filter(|l| {
            l.windows(2).all(|w| {
                let diff = w[1] - w[0];
                diff > 0 && diff <= 3
            }) || l.windows(2).all(|w| {
                let diff = w[1] - w[0];
                diff < 0 && diff >= -3
            })
        })
        .count();

    println!("P1 {}", safe_cnt);

    let safe_cnt_2 = lines
        .iter()
        .filter(|l| {
            (0..l.len()).any(|i| {
                let sub_seq: Vec<i32> = l
                    .iter()
                    .enumerate()
                    .filter_map(|(idx, &val)| if idx != i { Some(val) } else { None })
                    .collect();
                sub_seq.windows(2).all(|w| {
                    let diff = w[1] - w[0];
                    diff > 0 && diff <= 3
                }) || sub_seq.windows(2).all(|w| {
                    let diff = w[1] - w[0];
                    diff < 0 && diff >= -3
                })
            })
        })
        .count();

    println!("P2 {}", safe_cnt_2);
}
