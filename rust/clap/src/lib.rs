#[macro_use] extern crate lazy_static;
extern crate regex;
extern crate rusqlite;

pub mod weblog;

use regex::Regex;
use weblog::Weblog;
use rusqlite::Connection;

// Take an unprocessed string representing a single line of an Apache log,
// attempt to match the various components of the string, and generate a Weblog
// struct from them.  Returns None on error.
pub fn parse_weblog(line: &str) -> Option<Weblog> {
    lazy_static! {
        static ref RE: Regex = Regex::new("(?x)
            (\\S+)\\s
            (\\S+)\\s
            (\\S+)\\s
            \\[(\\d{2}/\\w+/\\d{4}:\\d{2}:\\d{2}:\\d{2}\\s+.+?)\\]\\s
            \"(\\w+\\s\\S+\\s\\w+/\\d+\\.\\d+)\"\\s
            (\\d+)\\s
            (\\d+)\\s
            \"(\\S+)\"\\s
            \"(.+)\"
            ").expect("Unable to compile Regex");
    }

    // This used to print to stdout before returning None, but the calling
    // program should do the printing.
    let cap = match RE.captures(line) {
        Some(x) => x,
        None => {
            return None;
        }
    };
    let logline = Weblog::new(
        cap[1].to_string(),
        cap[4].to_string(),
        cap[5].to_string(),
        cap[6].parse::<i32>().unwrap_or(0),
        cap[7].parse::<i32>().unwrap_or(0),
        cap[8].to_string(),
        cap[9].to_string()
    );
    Some(logline)
}

// Given a Weblog struct, connect to the database and create a new entry.
// Returns true on success, false on failure.
// TODO: Abstract out the connection part so the DB name isn't hard-coded
pub fn create(log: &Weblog) -> bool {
    let conn = Connection::open("test.db").expect("Cannot open database?");
    match conn.execute("INSERT INTO weblogs
                        (ipaddr, date, request, code, size, referer, agent)
                        VALUES ($1, $2, $3, $4, $5, $6, $7)",
                        &[&log.ip, &log.date, &log.req, &log.code, 
                          &log.size, &log.referer, &log.agent]) {
        Ok(_) => return true,
        Err(err) => {
            println!("Insert failed: {}", err);
            return false;
        }
    }
}

// Given an integer, connect to the database and retrieve that number of 
// entries.  Returns a Vec of Weblog structs.
pub fn fetch(count: i32) -> Vec<Weblog> {
    let conn = Connection::open("test.db").expect("Cannot open database?");
    let mut stmt = conn.prepare("SELECT * FROM weblogs LIMIT (?)")
        .expect("Unable to prepare SELECT statement");
    let log_iter = stmt.query_map(&[&count], |row| {
        Weblog {
            ip: row.get(0),
            date: row.get(1),
            req: row.get(2),
            code: row.get(3),
            size: row.get(4),
            referer: row.get(5),
            agent: row.get(6)
        }
    }).expect("Something went terribly wrong!");

    let mut v: Vec<Weblog> = vec![];

    for log in log_iter {
        v.push(log.unwrap());
    }
    v
}

// Connect to the database and create the weblogs table
pub fn create_table() -> bool {
    let conn = Connection::open("test.db").expect("Cannot open database?");

    match conn.execute("CREATE TABLE weblogs (
                  ipaddr varchar(50) not null,
                  date varchar(50) not null,
                  request varchar(255) not null,
                  code int not null,
                  size int not null default 0,
                  referer varchar(255) not null,
                  agent varchar(255) not null,
                  primary key (ipaddr, date))", &[]) {
        Ok(_) => true,
        Err(e) => {
            println!("Error creating table: {}", e);
            false
        }
    }
}
