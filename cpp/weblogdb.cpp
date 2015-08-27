// Define stuff here
#include <iostream>
#include <string>
#include <vector>
#include <pcre++.h>
#include <sqlite3.h>
#include "weblogdb.h"

using std::string;

Weblogdb::Weblogdb(string file) {
    const char *cfile = file.c_str();
    rc = sqlite3_open(cfile, &db);
    if ( rc ) {
        std::cout << "Can't open database:" << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

Weblogdb::Weblogdb() { db = NULL; }

Weblogdb::~Weblogdb() {
    sqlite3_close(db);
}

void Weblogdb::setDbFile(string file) {
    const char *cfile = file.c_str();
    rc = sqlite3_open(cfile, &db);
    if ( rc ) {
        std::cout << "Can't open database:" << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

bool Weblogdb::write(Weblog& log) {
    char buffer [1024];
    sprintf(buffer, "INSERT into weblogs (ipaddr, date, request, code, size, referer, agent) " \
                    "values (\"%s\", \"%s\", \"%s\", \"%d\", \"%d\", \"%s\", \"%s\");", 
                    log.ip_addr.c_str(), log.date.c_str(), log.request.c_str(),
                    log.code, log.size, log.referer.c_str(), log.agent.c_str());
    std::cout << buffer << std::endl;
    rc = sqlite3_exec(db, buffer, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    } else {
        std::cout << "Created record ok" << std::endl;
        return true;
    }
}

std::vector<Weblog> Weblogdb::fetch(string query) {
    std::vector<Weblog> foo;
    return foo;
}

static int callback(void *victor, int argc, char **argv, char **azColName) {
    // Callback is called for every retrieved dataset.
    // victor should be a pointer to our Weblog vector.
    // azColName is an array holding the column name.
    // argv is an arrya holding the value
    // ipaddr/date/request/code/size/referer/agent
    //   0     1     2      3    4     5       6
    std::vector<Weblog>* v = (std::vector<Weblog>*) victor;
    Weblog w;
    w.ip_addr = argv[0];
    w.date = argv[1];
    w.request = argv[2];
    w.code = atoi(argv[3]);
    w.size = atoi(argv[4]);
    w.referer = argv[5];
    w.agent = argv[6];
    v->push_back(w);
    return 0;
}

std::vector<Weblog> Weblogdb::fetch_all(int limit /*= 50*/) {
    std::vector<Weblog> logs;
    std::vector<Weblog>* logptr = &logs;
    char sql [50];
    sprintf(sql, "SELECT * FROM weblogs limit %d", limit);
    rc = sqlite3_exec(db, sql, callback, (void*)logptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Executed select ok!" << std::endl;
    }
    return logs;
}

void Weblogdb::createTables() {
    const char *sql = "create table weblogs(" \
                    "ipaddr varchar(50) not null," \
                    "date varchar(50) not null," \
                    "request varchar(255) not null," \
                    "code int not null," \
                    "size int not null default 0," \
                    "referer varchar(255) not null," \
                    "agent varchar(255) not null, " \
                    "primary key (ipaddr, date) );";
    // Make sure the DB is open
    if (!db) {
        std::cout << "Database isn't open yet, can't create tables." << std::endl;
        return;
    }
    // ok good now execute the sql
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    else {
        std::cout << "Table created ok!" << std::endl;
    }
}

