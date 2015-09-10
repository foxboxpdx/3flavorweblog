// Library for parsing apache logs
// Declaration of struct
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "weblog.h"

Weblog::Weblog() { }

std::ostream& operator<<(std::ostream& os, const Weblog& w) {
    std::ostringstream foo;
    foo << w.ip_addr << std::setw(20) << std::setfill(' ') << std::left;
    foo << w.date << std::setw(30) << std::setfill(' ') << std::left;
    foo << w.request << std::setw(40) << std::setfill(' ') << std::left;
    return os << foo.str();
}

std::istream& operator>>(std::istream& is, Weblog& ww) {
    std::string ip, dt, rq, co, sz, rf, ag;
    is >> ip >> dt >> rq >> co >> sz >> rf >> ag;
    ww.ip_addr = ip;
    ww.date = dt;
    ww.request = rq;
    ww.code = atoi(co.c_str());
    ww.size = atoi(sz.c_str());
    ww.referer = rf;
    ww.agent = ag;
    return is;
}

bool operator==(const Weblog& a, const Weblog& b) {
    return a.ip_addr==b.ip_addr && a.date==b.date;
}

bool operator!=(const Weblog& a, const Weblog& b) {
    return !(a==b);
}
