// Weblog parser module
use regex::Regex;
use weblog::Weblog;

pub fn parse_weblog(line: &str) -> Weblog {
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
            ").unwrap();
    }

    let mut v: Vec<Weblog> = vec![];

    for cap in RE.captures_iter(line) {
        let logline = Weblog::new(
	    cap[1].to_string(),
	    cap[4].to_string(),
	    cap[5].to_string(),
	    cap[6].parse::<i32>().unwrap_or(0),
	    cap[7].parse::<i32>().unwrap_or(0),
	    cap[8].to_string(),
	    cap[9].to_string()
        );
        v.push(logline);
    }
    v.pop().unwrap()
}
