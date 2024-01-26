#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
// #include <thread>
#include <vector>

using namespace std;

int main() {
    smatch m;
    string str = "#include\"dir1/b.h\"\n";
    // static const regex includ_file(R"/(\s*#\s*include\s*"([^"]*)"\s*)/");
     //  static const regex includ_file(R"/(\s*#\s*include\s*"([^"]*)"\s*)/");
    static const regex includ_file(R"/(\s*#\s*include[\w\W]*)/");
    if (regex_match(str, m, includ_file)) {
        cout << string(m[0]) << endl;
        cout << string(m[1]) << endl;
    }
    return 0;
}