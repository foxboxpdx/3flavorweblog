// Read from a log file and put contents into WeblogDB
#include <iostream>
#include <string>
#include <fstream>
#include "weblogdb.h"
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 2) {
      cout << "Usage: " << endl << "\t" << argv[0] << " parse <filename>" << endl;
      cout << "\t" << argv[0] << " fetch <num records>" << endl;
      cout << "\t" << argv[0] << " create table" << endl;
      exit(1);
    }

    // This is a messy and dumb way of comparing the command arguments
    char *command = argv[1];
    string a = "parse";
    string b = "fetch";
    string c = "create";
    if (a.compare(command) == 0) {
        char *logFile = argv[2];
        Weblogdb foo = Weblogdb("test.db");
        Parser p = Parser(foo);

        // Read through the file and do a thing
        ifstream in(logFile);
        string line;
        while (getline(in, line)) {
            p.parseWeblog(line);
        }
        in.close();

        // Check count
        cout << "Number of logs parsed: " << p.count() << endl;

        // Dump to database
        p.toDatabase();
        cout << "Wrote logs to database." << endl;
    }
    if (b.compare(command) == 0) {
        int count = atoi(argv[2]);
        Weblogdb foo = Weblogdb("test.db");
        vector<Weblog> logs = foo.fetch_all(count);
        for (auto &wl : logs) {
            cout << wl << endl;
        }
    }
    if (c.compare(command) == 0) {
        Weblogdb foo = Weblogdb("test.db");
        foo.createTables();
        cout << "Created tables!" << endl;
    }

    // End!
    return 0;
}
