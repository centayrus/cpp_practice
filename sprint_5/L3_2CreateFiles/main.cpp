#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

// реализуйте эту функцию:
void CreateFiles(const string& config_file) {
    string line, text;
    ifstream in_file(config_file);
    ofstream out_file(line);
    out_file.close();
    while (getline(in_file, line)) {
        if (line[0] != '>') {
            // закрытие файла. Если не закрыть, то не получится открыть поток записи в другой файл
           out_file.close();
            // открытие файла
            out_file.open(line);
        } else {
           // запись строки начиная со второго символа
            out_file << line.substr(1) << endl;
        }
    }
}

string GetLine(istream& in) {
    string s;
    getline(in, s);
    return s;
}

int main() {
    ofstream("test_config.txt"s) << "shakespeare/a.txt\n"
                                    ">10\n"
                                    ">abc\n"
                                    "b.txt\n"
                                    ">123"s;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    //  assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    // assert(GetLine(in_b) == "123"s);
}