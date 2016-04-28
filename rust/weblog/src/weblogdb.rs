// It's the database component using sqlite3 from rusqlite
use weblog::Weblog;
use rusqlite::Connection;

pub fn write(log: Weblog) {
    let conn = Connection::open("test.db").unwrap();
    match conn.execute("INSERT INTO weblogs (ipaddr, date, request, code, size, referer, agent)
                        VALUES ($1, $2, $3, $4, $5, $6, $7)",
                        &[&log.ip, &log.date, &log.req, &log.code, &log.size, &log.referer, &log.agent]) {
        Ok(_) => println!("Insert okay"),
        Err(err) => println!("Insert failed: {}", err),
    }
}

pub fn fetch_all() -> Vec<Weblog> {
    let conn = Connection::open("test.db").unwrap();
    let mut stmt = conn.prepare("SELECT * FROM weblogs").unwrap();
    let log_iter = stmt.query_map(&[], |row| {
        Weblog {
            ip: row.get(0),
            date: row.get(1),
            req: row.get(2),
            code: row.get(3),
            size: row.get(4),
            referer: row.get(5),
            agent: row.get(6)
        }
    }).unwrap();

    let mut v: Vec<Weblog> = vec![];

    for log in log_iter {
        v.push(log.unwrap());
    }
    v
}
