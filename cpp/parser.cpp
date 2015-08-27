// Define stuff here
#include <iostream>
#include <string>
#include <vector>
#include <pcre++.h>
#include "parser.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::stoi;
using pcrepp::Pcre;

Parser::Parser(Weblogdb& d) {
    database = d;
    logs = vector<Weblog>();
}

void Parser::parseWeblog(string line) {
    // Hoping pcre can save me here
    const string pattern =  "(\\S+)\\s(\\S+)\\s(\\S+)\\s\\[(\\d{2}/\\w+/\\d{4}\\:\\d{2}\\:\\d{2}\\:\\d{2}\\s+.+?)\\]\\s\\\"(\\w+\\s\\S+\\s\\w+\\/\\d+\\.\\d+)\\\"\\s(\\d+)\\s(\\d+|-)\\s\\\"(\\S+)\\\"\\s\\\"(.+)\\\"";
    // Prep a Weblog object
    Weblog w;

    // Call upon the mighty powers of PCRE
    Pcre p(pattern);
    if (p.search(line) == true) {
        if (p.matches() == 9) {
            // Should get 9 matches out of an apache log
            w.ip_addr = p[0];
            w.date = p[3];
            w.request = p[4];
            w.code = stoi(p[5]);
            w.size = stoi(p[6]);
            w.referer = p[7];
            w.agent = p[8];
        }
        else {
            cout << "Input string didn't match properly." << endl;
        }
    }
    else {
        cout << "Input string didn't match pattern at all." << endl;
    }

    // Shove the Weblog into the private logs vector
    logs.push_back(w);

    // Done!
}
