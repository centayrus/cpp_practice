#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}
 
void PrintTree(ostream& dst, const path& p, /* const filesystem::file_status& status, */ int offset) {
    error_code err;
    offset += 2;
    std::vector<pair<filesystem::path, filesystem::file_status>> path_obj;
    for (const auto& dir_entry : filesystem::directory_iterator(p)) {
        auto status = filesystem::status(dir_entry.path(), err);
        path_obj.push_back({dir_entry.path(), status});
    }
    sort(path_obj.begin(), path_obj.end(), [](const pair<filesystem::path, filesystem::file_status>& s1, const pair<filesystem::path, filesystem::file_status>& s2) {
        return s1.first.filename().string() > s2.first.filename().string();
    });
    for (const auto& [path, status] : path_obj) {
        dst << string(offset, ' ') << path.filename().string() << std::endl;
        std::cout << string(offset, ' ') << path.filename().string() << std::endl;
        if (status.type() == filesystem::file_type::directory) {
            PrintTree(dst, path, offset);
        }
    }
}

void PrintTree(ostream& dst, const path& p) {
    cout << p.filename().string() << endl;
    dst << p.filename().string() << endl;
    int offset = 0;
    PrintTree(dst, p, offset);
}

int main() {
    error_code err;
   filesystem::remove_all("test_dir", err);
   filesystem::create_directories("test_dir"_p / "a"_p, err);
   filesystem::create_directories("test_dir"_p / "b"_p, err);
   filesystem::create_directories("test_dir"_p / "b"_p / "c"_p, err);
   filesystem::create_directories("test_dir"_p / "b"_p / "c"_p / "d"_p, err);
   filesystem::create_directories("test_dir"_p / "b"_p / "c"_p / "z"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);
    ofstream("test_dir"_p / "b"_p / "c"_p / "f3.txt"_p);
    ofstream("test_dir"_p / "b"_p / "c"_p / "f5.txt"_p);
    ofstream("test_dir"_p / "b"_p / "c"_p / "f7.txt"_p);
    ofstream("test_dir"_p / "b"_p / "c"_p / "d"_p / "f1.txt"_p);

    ostringstream out;
    PrintTree(out, "test_dir"_p);
    // assert(out.str() ==
    //     "test_dir\n"
    //     "  b\n"
    //     "    f2.txt\n"
    //     "    f1.txt\n"
    //     "  a\n"
    //     "    f3.txt\n"s
    // );
}