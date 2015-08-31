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
    // Trying to make this a little safer using prepared statements and binding values
    sqlite3_stmt* sth;

    // Statement with binding markers
    string q = "INSERT OR IGNORE INTO weblogs "
               "(ipaddr, date, request, code, size, referer, agent) "
               "values ( ? , ? , ? , ? , ? , ? , ? )";
    rc = sqlite3_prepare_v2(db, q.c_str(), -1, &sth, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error code: " << rc << std::endl;
        return false;
    }
    // Bind stuff
    sqlite3_bind_text(sth, 1, log.ip_addr.c_str(), 50, SQLITE_STATIC);
    sqlite3_bind_text(sth, 2, log.date.c_str(),    50, SQLITE_STATIC);
    sqlite3_bind_text(sth, 3, log.request.c_str(), 1024, SQLITE_STATIC);
    sqlite3_bind_int( sth, 4, log.code);
    sqlite3_bind_int( sth, 5, log.size);
    sqlite3_bind_text(sth, 6, log.referer.c_str(), 1024, SQLITE_STATIC);
    sqlite3_bind_text(sth, 7, log.agent.c_str(),   512, SQLITE_STATIC);

    // Execute the prepared statement and check for success
    rc = sqlite3_step(sth);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << rc << std::endl;
        sqlite3_finalize(sth);
        return false;
    } else {
        sqlite3_finalize(sth);
        return true;
    }
}

// This is not a particularly safe way to do this!
// This function should probably only be called by a program
// with very strict query checking!
std::vector<Weblog> Weblogdb::fetch(string query) {
    // Even using prepared statements this isn't terribly safe,
    // but it lets us get rid of that callback function BS.
    std::vector<Weblog> logs;
    sqlite3_stmt* sth;

    // Prepare select statement
    string q = "SELECT * FROM weblogs WHERE ?";
    rc = sqlite3_prepare_v2(db, q.c_str(), -1, &sth, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error code: " << rc << std::endl;
        return logs;
    }

    // Bind
    sqlite3_bind_text(sth, 1, query.c_str(), -1, SQLITE_STATIC);

    // Execute and iterate
    while (sqlite3_step(sth) == SQLITE_ROW) {
        Weblog w;
        w.ip_addr = reinterpret_cast<const char*>(sqlite3_column_text(sth, 0));
        w.date = reinterpret_cast<const char*>(sqlite3_column_text(sth, 1));
        w.request = reinterpret_cast<const char*>(sqlite3_column_text(sth, 2));
        w.code = sqlite3_column_int(sth, 3);
        w.size = sqlite3_column_int(sth, 4);
        w.referer = reinterpret_cast<const char*>(sqlite3_column_text(sth, 5));
        w.agent = reinterpret_cast<const char*>(sqlite3_column_text(sth, 6));
        logs.push_back(w);
    }
    return logs;
}

std::vector<Weblog> Weblogdb::fetch_all(int limit /*= 50*/) {
    // Using a prepared statement here allows us to forego
    // the use of a callback function, which is nice.
    sqlite3_stmt* sth;
    std::vector<Weblog> logs;

    // Prepare select statement
    string q = "SELECT * FROM weblogs LIMIT ?";
    rc = sqlite3_prepare_v2(db, q.c_str(), -1, &sth, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error code: " << rc << std::endl;
        return logs;
    }
    // Bind the limit to the statement
    sqlite3_bind_int(sth, 1, limit);
    
    // Execute the prepared statement
    // Note: sqlite3 is kind of dumb in how column_text operates, since
    // it returns an unsigned char that we must call reinterpret_cast on.
    // This totes works though, I promise.
    while (sqlite3_step(sth) == SQLITE_ROW) {
        Weblog w;
        w.ip_addr = reinterpret_cast<const char*>(sqlite3_column_text(sth, 0));
        w.date = reinterpret_cast<const char*>(sqlite3_column_text(sth, 1));
        w.request = reinterpret_cast<const char*>(sqlite3_column_text(sth, 2));
        w.code = sqlite3_column_int(sth, 3);
        w.size = sqlite3_column_int(sth, 4);
        w.referer = reinterpret_cast<const char*>(sqlite3_column_text(sth, 5));
        w.agent = reinterpret_cast<const char*>(sqlite3_column_text(sth, 6));
        logs.push_back(w);
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

