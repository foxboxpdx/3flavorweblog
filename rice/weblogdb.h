// Library for parsing apache logs
// Header for weblogdb class
#include <string>
#include <vector>
#include <sqlite3.h>
#include <iostream>
#include "weblog.h"

#ifndef WEBLOGDB_H
#define WEBLOGDB_H
namespace LibWeblog {
    class Weblogdb {
        public:
            Weblogdb(std::string file);
            Weblogdb();
            ~Weblogdb();
            bool write(Weblog& log);
            std::vector<Weblog> fetch(std::string query);
            std::vector<Weblog> fetch_all(int limit = 50);
            void setDbFile(std::string file);
            void createTables();
        private:
            sqlite3 *db;
            char *zErrMsg;
            int rc;
    };
}
#endif
