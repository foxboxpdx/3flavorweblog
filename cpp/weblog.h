// Library for parsing apache logs
// Declaration of struct
#include <string>
#include <vector>

#ifndef WEBLOG_H
#define WEBLOG_H
struct Weblog { 
    std::string ip_addr;
    std::string date;
    std::string request;
    int code;
    int size;
    std::string referer;
    std::string agent;

    friend std::ostream& operator<<(std::ostream& os, const Weblog& w) {
        char buffer [1024];
        sprintf (buffer, "%-20s %-30s %-40s", w.ip_addr.c_str(), w.date.c_str(), w.request.c_str());
        return os << buffer;
    }

    friend std::istream& operator>>(std::istream& is, Weblog& ww) {
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

    friend bool operator==(const Weblog& a, const Weblog& b) {
        return a.ip_addr==b.ip_addr && a.date==b.date;
    }

    friend bool operator!=(const Weblog& a, const Weblog& b) {
        return !(a==b);
    }
};
#endif
