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
using filesystem::path;

path operator""_p(const char *data, std::size_t sz) {
    return path(data, data + sz);
}
path LocalDirSearch(const path &parent, const path& inc_path) {
    error_code err;
    path find_path, empty_path;
    for (const auto &dir_entry : filesystem::directory_iterator(parent / inc_path.parent_path(), err )) { // 
        path p = inc_path.filename().string();
        if (dir_entry.path().filename().string() == p && dir_entry.status().type() == filesystem::file_type::regular) {
                find_path = dir_entry.path();
               ifstream in_check(dir_entry.path());
               if (in_check) {
                 return find_path;
               }
        }
    }
    return empty_path;
}

path VectorDirSearch(const path &inc_path, const vector<path> &include_directories) {
    error_code err;
    path find_path, empty_path;
    for (const auto &v_path : include_directories) {
        for (const auto &dir_entry : filesystem::directory_iterator(v_path / inc_path.parent_path(), err)) { // 
            if (dir_entry.path().filename().string() == inc_path.filename().string() && dir_entry.status().type() == filesystem::file_type::regular) {             
                find_path = dir_entry.path();
        //        cout << find_path << endl;
              ifstream in_check(dir_entry.path());
              if (in_check) {
                return find_path;
              } 
        }
        }
    }
    return empty_path;
}

bool Preprocess(const path &in_file, const path &out_file, const path &cur_file, const vector<path> &include_directories) {
    smatch m;
    string str;
  //  cout << "in_file: "s << in_file << endl;
   path parent = in_file.parent_path();
    static const regex includ_file(R"/(\s*#\s*include\s*"([^"]*)"\s*)/");
    static const regex includ_lib(R"/(\s*#\s*include\s*<([^>]*)>\s*)/");
    ifstream in(in_file);
   while (!in) {
       continue;
   }
    ofstream out(out_file, ios::app);
    while (getline(in, str)) {
        path inc_path;
        if (regex_match(str, m, includ_file)) {
            inc_path = string(m[1]);
            path local_path = LocalDirSearch(parent, inc_path);
            if (!local_path.empty()) {
                Preprocess(parent / inc_path, out_file, in_file, include_directories);
                continue;
            } else {
                path vector_path = VectorDirSearch(inc_path, include_directories);
                if (!vector_path.empty()) {
                    Preprocess(vector_path, out_file, in_file, include_directories);
                    continue;
                }
            }
        cout << "unknown include file "s << inc_path.filename().string() << " at file "s << cur_file.string() << " at line "s << 8 << endl;
        return false;

        } else if (regex_match(str, m, includ_lib)) {
            inc_path = string(m[1]);
            path vector_path = VectorDirSearch(inc_path, include_directories);
          //  cout << "vector_path: "s << vector_path << endl;
            if (!vector_path.empty()) {
                Preprocess(vector_path, out_file, in_file, include_directories);
                    continue;
            }
        cout << "unknown include file "s << inc_path.filename().string() << " at file "s << cur_file.string() << " at line "s << 8 << endl; 
        return false;  
        }
        

        out << str << endl;
    }
    return true;
}

bool Preprocess(const path &in_file, const path &out_file, const vector<path> &include_directories) {
    ifstream in(in_file);
    if (!in) {
        return false;
    }
  //  path p = in_file.filename().string();
    return Preprocess(in_file, out_file, in_file, include_directories);
}

string GetFileContents(string file) {
    ifstream stream(file);

    // конструируем string по двум итераторам
    return {(istreambuf_iterator<char>(stream)), istreambuf_iterator<char>()};
}

void Test() {
    error_code err;
    filesystem::remove_all("sources"_p, err);
    filesystem::create_directories("sources"_p / "include2"_p / "lib"_p, err);
    filesystem::create_directories("sources"_p / "include1"_p, err);
    filesystem::create_directories("sources"_p / "dir1"_p / "subdir"_p, err);

    {
        ofstream file("sources/a.cpp");
        file << "// this comment before include\n"
                "#include \"dir1/b.h\"\n"
                "// text between b.h and c.h\n"
                "#include \"dir1/d.h\"\n"
                "\n"
                "int SayHello() {\n"
                "    cout << \"hello, world!\" << endl;\n"
                "#   include<dummy.txt>\n"
                "}\n"s;
    }
    {
        ofstream file("sources/dir1/b.h");
        file << "// text from b.h before include\n"
                "#include \"subdir/c.h\"\n"
                "// text from b.h after include"s;
    }
    {
        ofstream file("sources/dir1/subdir/c.h");
        file << "// text from c.h before include\n"
                "#include <std1.h>\n"
                "// text from c.h after include\n"s;
    }
    {
        ofstream file("sources/dir1/d.h");
        file << "// text from d.h before include\n"
                "#include \"lib/std2.h\"\n"
                "// text from d.h after include\n"s;
    }
    {
        ofstream file("sources/include1/std1.h");
        file << "// std1\n"s;
    }
    {
        ofstream file("sources/include2/lib/std2.h");
        file << "// std2\n"s;
    }
    // Preprocess("sources"_p / "a.cpp"_p, "sources"_p / "a.in"_p, {"sources"_p / "include1"_p, "sources"_p / "include2"_p});
    //                      {"sources"_p / "include1"_p, "sources"_p / "include2"_p});
     assert((!Preprocess("sources"_p / "a.cpp"_p, "sources"_p / "a.in"_p,
                         {"sources"_p / "include1"_p, "sources"_p / "include2"_p})));

    ostringstream test_out;
    test_out << "// this comment before include\n"
                "// text from b.h before include\n"
                "// text from c.h before include\n"
                "// std1\n"
                "// text from c.h after include\n"
                "// text from b.h after include\n"
                "// text between b.h and c.h\n"
                "// text from d.h before include\n"
                "// std2\n"
                "// text from d.h after include\n"
                "\n"
                "int SayHello() {\n"
                "    cout << \"hello, world!\" << endl;\n"s;
    GetFileContents("sources/a.in"s);
     assert(GetFileContents("sources/a.in"s) == test_out.str());
}

int main() {
    Test();
}

// for (const auto &dir_entry : filesystem::directory_iterator(parent / inc_path.parent_path())) {
//     path p = inc_path.filename().string();
//     if (dir_entry.path().filename().string() == p && dir_entry.status().type() == filesystem::file_type::regular) {
//         is_find_file = true;
//         out.close();
//         Preprocess(parent / inc_path, out_file, inc_path.filename().string(), include_directories);
//         break;
//     }
// }