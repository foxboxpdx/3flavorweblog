extern crate weblog;
use std::env;
use std::fs::File;
use std::io::BufReader;
use std::io::BufRead;
use weblog::weblog::Weblog;

fn main() {
    // Check args
    let args: Vec<String> = env::args().collect();
    if args.len() <= 2 {
        println!("Usage:\n\t{:?} parse <filename>", &args[0]);
        println!("\t{:?} fetch <num records>", &args[0]);
        println!("\t{:?} create table", &args[0]);
        return;
    }

    let action: &str = &args[1];
    match action {
        // Parse a file
        "parse" => do_parse(&args[2]),
        // Fetch some records
        "fetch" => do_fetch(&args[2]),
        // Make the table
        "create" => do_create(),
        // Else
        _ => println!("Unknown argument: {}", action),
    }
}

fn do_parse(filename: &str) {
    // Open up your file and let it flow into me
    let f = match File::open(filename) {
        Ok(file) => file,
        Err(e) => {
            println!("{}", e);
            return;
        }
    };
    let reader = BufReader::new(&f);
    let mut weblogs: Vec<Weblog> = vec![];
    for line in reader.lines() {
        let l = line.unwrap();
        let v = weblog::parser::parse_weblog(&l);
        weblogs.push(v);
    }

    println!("Processed {} records.", weblogs.len());
}

fn do_fetch(records: &str) {

}

fn do_create() {

}
