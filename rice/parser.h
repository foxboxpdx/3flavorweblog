// Library for parsing apache logs
// Header for parser class
#include <string>
#include <vector>
#include "weblogdb.h"
#include "weblog.h"

#ifndef PARSER_H
#define PARSER_H
class Parser {
    public:
        Parser(Weblogdb& d);
        Parser();
        void parseWeblog(std::string line);
        int count();
        bool toDatabase();
        void toString();
    private:
        std::vector<Weblog> logs;
        Weblogdb database;
};
#endif
