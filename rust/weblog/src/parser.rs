// Weblog parser module
use regex::Regex;

//fn parse_weblog(line: String) {
pub fn parse_weblog() {
    let re = Regex::new("(?x)
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

    // Example line here
    let example = "127.0.0.1 - frank [10/Oct/2000:13:55:36 -0700] \"GET /apache_pb.gif HTTP/1.0\" 200 2326 \"http://www.example.com/start.html\" \"Mozilla/4.08 [en] (Win98; I ;Nav)\"";

    for cap in re.captures_iter(example) {
        println!("IP: {} x: {} x: {} date: {} req: {} code: {} size: {} ref: {} agent: {}",
                 cap.at(1).unwrap_or(""),
                 cap.at(2).unwrap_or(""),
                 cap.at(3).unwrap_or(""),
                 cap.at(4).unwrap_or(""),
                 cap.at(5).unwrap_or(""),
                 cap.at(6).unwrap_or(""),
                 cap.at(7).unwrap_or(""),
                 cap.at(8).unwrap_or(""),
                 cap.at(9).unwrap_or(""));
    }
}
