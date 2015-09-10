// Library for parsing apache logs
// Declaration of struct
#include <string>
#include <vector>
#include <iomanip>

#ifndef WEBLOG_H
#define WEBLOG_H
class Weblog {
    public:
        Weblog();
        friend std::ostream& operator<<(std::ostream& os, const Weblog& w);
        friend std::istream& operator>>(std::istream& is, Weblog& ww);
        friend bool operator==(const Weblog& a, const Weblog& b);
        friend bool operator!=(const Weblog& a, const Weblog& b);
        std::string ip_addr;
        std::string date;
        std::string request;
        int code;
        int size;
        std::string referer;
        std::string agent;
};
#endif
