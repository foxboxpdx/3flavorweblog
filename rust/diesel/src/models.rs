use std::fmt;
use super::schema::weblogs;

#[derive(Queryable, Insertable)]
#[table_name="weblogs"]
pub struct Weblog {
    pub ipaddr: String,
    pub date: String,
    pub request: String,
    pub code: i32,
    pub size: i32,
    pub referer: String,
    pub agent: String
}

impl Weblog {
    pub fn new(ip: String, date: String, req: String, code: i32, size: i32, referer: String, agent: String) -> Weblog {
        Weblog { ipaddr:      ip,
                 date:    date,
                 request: req,
                 code:    code,
                 size:    size,
                 referer: referer,
                 agent:   agent 
        }
    }
}

impl Eq for Weblog {}

impl PartialEq for Weblog {
    fn eq(&self, other: &Self) -> bool {
        self.ipaddr == other.ipaddr && self.date == other.date
    }
}

impl fmt::Display for Weblog {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {}. {}. {}. {}. {}. {})",
               self.ipaddr, self.date, self.request, self.code,
               self.size, self.referer, self.agent)
    }
}
