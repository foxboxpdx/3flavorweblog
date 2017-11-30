#[macro_use]
extern crate clap;
extern crate weblog;

use clap::App;
use self::weblog::*;
use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;

//use self::weblog::Weblog;

// Handle inputs and call specific functions
fn main() {
    let yaml = load_yaml!("cli.yml");
    let matches = App::from_yaml(yaml).get_matches();

    // Look for calls to 'parse'
    if let Some(matches) = matches.subcommand_matches("parse") {
        if matches.is_present("filename") {
            do_parse(matches.value_of("filename").unwrap());
        }
        return;
    }


    // Look for calls to 'fetch'
    if let Some(matches) = matches.subcommand_matches("fetch") {
        if matches.is_present("count") {
            do_fetch(matches.value_of("count").unwrap());
        }
        return;
    }

    // Look for calls to 'manage'
    if let Some(matches) = matches.subcommand_matches("manage") {
        if matches.is_present("action") {
            do_manage(matches.value_of("action").unwrap());
        }
        return;
    }
}

// Parse a file
fn do_parse(fname: &str) -> bool {
    // Attempt to open and read in the supplied filename
    let f = match File::open(fname) {
        Ok(file) => file,
        Err(e) => {
            println!("Error opening file: {}", e);
            return false;
        }
    };
    let reader = BufReader::new(&f);
    let mut count = 0;
    for line in reader.lines() {
        let l = line.expect("Couldn't get line?");
        let wl = match parse_weblog(&l) {
            Some(x) => x,
            None => {
                println!("Unable to parse: {}", l);
                continue;
            }
        };
        create(&wl);
        count += 1;
    }
    println!("Successfully processed {} log entries.", count);
    true
}

// Fetch some records - 'count' comes in as a string, remember to parse to i32.
fn do_fetch(count: &str) -> bool {
    // Parse count, make sure it's a number
    let icount: i32 = match count.parse() {
        Ok(n) => n,
        Err(_) => {
            println!("Error, {} is not an integer.", count);
            return false;
        }
    };
    // Call fetch and print the return value
    let recs = fetch(icount);
    for w in recs {
        println!("{}", w);
    }
    true
}

// Manage database
fn do_manage(action: &str) -> bool {
    // Check value of action and act accordingly
    match action {
        "create" =>  create_table(),
        "destroy" => drop_table(),
        "status" =>  db_status(),
        _ => {
            println!("Unknown action: {}", action);
            return false;
        }
    };
    true
}

