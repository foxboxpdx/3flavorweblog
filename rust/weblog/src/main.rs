extern crate weblog;

fn main() {
    let v = weblog::parser::parse_weblog();
    for i in &v {
        println!("It's a weblog line! {}", i);
    }
}
