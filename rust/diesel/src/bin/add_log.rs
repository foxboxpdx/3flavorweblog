extern crate weblog;
extern crate diesel;

use self::weblog::*;
use std::env::args;
use self::models::Weblog;

fn main() {
    let conn = connect();
    // Read args
    let ip = args().nth(1).expect("IPAddr expected.");
    let date = args().nth(2).expect("Date expected.");
    let request = args().nth(3).expect("Request string expected.");
    let code_s = args().nth(4).expect("Return code expected.");
    let code : i32 = match code_s.parse() {
        Ok(n) => {
            n
        },
        Err(_) => {
            println!("Error: Code must be an integer");
            return;
        },
    };
    let size_s = args().nth(5).expect("Data size expected.");
    let size : i32 = match size_s.parse() {
        Ok(n) => {
            n
        },
        Err(_) => {
            println!("Error: Size must be an integer");
            return;
        },
    };
    let referer = args().nth(6).expect("Referer string expected.");
    let agent = args().nth(7).expect("Agent string expected.");

    let log = Weblog::new(ip, date, request, code, size, referer, agent);
    create(&conn, &log);
}
