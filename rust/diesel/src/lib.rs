#[macro_use] extern crate diesel;
//#[macro_use] extern crate diesel_infer_schema;
#[macro_use] extern crate lazy_static;
extern crate dotenv;
extern crate regex;

use diesel::prelude::*;
use diesel::sqlite::SqliteConnection;
use dotenv::dotenv;
use std::env;
use self::models::Weblog;

pub mod schema;
pub mod models;

pub fn connect() -> SqliteConnection {
    dotenv().ok();

    let dburl = env::var("DATABASE_URL").expect("DATABASE_URL must be set");
    SqliteConnection::establish(&dburl).expect("Error connecting to DB")
}

pub fn create<'a>(conn: &SqliteConnection, log: &'a Weblog) {
    use schema::weblogs;

    diesel::insert_into(weblogs::table)
        .values(log)
        .execute(conn)
        .expect("Error saving new log");
}

// Parse a string from a file into a Weblog struct
use regex::Regex;

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

    let cap = match RE.captures(line) {
        Some(x) => x,
        None => {
            println!("Cannot parse line {}", line);
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

