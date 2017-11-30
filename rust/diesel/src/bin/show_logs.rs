extern crate weblog;
extern crate diesel;

use self::weblog::*;
use self::weblog::models::*;
use self::diesel::prelude::*;

fn main() {
    use weblog::schema::weblogs::dsl::*;

    let connection = connect();
    let results = weblogs.limit(50)
        .load::<Weblog>(&connection)
        .expect("Error loading weblog entries");

    println!("Displaying {} logs", results.len());
    for w in results {
        println!("{}", w);
    }
}

