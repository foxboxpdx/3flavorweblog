extern crate weblog;
extern crate diesel;

use self::weblog::*;
use std::env::args;
use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;

fn main() {
    let conn = connect();
    // Read args
    let fname = match args().nth(1) {
        Some(name) => name,
        None => {
            println!("Filename required");
            return
        }
    };

    // Open file
    let fh = match File::open(fname) {
        Ok(file) => file,
        Err(e) => {
            println!("{}", e);
            return;
        }
    };
    let reader = BufReader::new(&fh);
    
    // Process line by line
    for line in reader.lines() {
        let l = line.unwrap();
        let w = match parse_weblog(&l) {
            Some(x) => x,
            None => {
                continue;
            }
        };
        create(&conn, &w);
    }
}

