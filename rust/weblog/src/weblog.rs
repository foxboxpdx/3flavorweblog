use std::fmt;

// Define a weblog struct
#[derive(Debug)]
pub struct Weblog {
    pub ip: String,
    pub date: String,
    pub req: String,
    pub code: i32,
    pub size: i32,
    pub referer: String,
    pub agent: String,
}

impl Weblog {
    pub fn new(ip: String, date: String, req: String, code: i32, size: i32, referer: String, agent: String) -> Weblog {
        Weblog { ip: ip, date: date, req: req, code: code, size: size, referer: referer, agent: agent }
    }
}

impl Eq for Weblog {}

impl PartialEq for Weblog {
    fn eq(&self, other: &Self) -> bool {
        self.ip == other.ip && self.date == other.date
    }
}

impl fmt::Display for Weblog {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {}, {}, {}, {}, {}, {})",
               self.ip, self.date, self.req, self.code,
               self.size, self.referer, self.agent)
    }
}
