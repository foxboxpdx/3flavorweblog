// Testing executable
#include <iostream>
#include <string>
#include "weblogdb.h"
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    Weblogdb foo = Weblogdb();

    // Set filename
    foo.setDbFile("test.db");

    // Create table
    //foo.createTables();
    /*
    Weblog bar;
    bar.ip_addr = "10.0.0.1";
    bar.date = "[26/Aug/2015:00:31:35]";
    bar.request = "GET /index.html HTTP/1.1";
    bar.code = 200;
    bar.size = 1024;
    bar.referer = "-";
    bar.agent = "Big Billy Bob's Browser 1.0";
    foo.write(bar);
    */
    vector<Weblog> w;
    w = foo.fetch_all();
    for (auto &i : w) {
        cout << i << endl;
    }
}
