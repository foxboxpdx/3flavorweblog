#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
    }
}

#[macro_use] extern crate lazy_static;
extern crate regex;
extern crate rusqlite;

pub mod weblog;
pub mod parser;
pub mod weblogdb;
