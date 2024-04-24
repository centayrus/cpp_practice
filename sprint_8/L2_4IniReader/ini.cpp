#include "ini.h"

using namespace std;

namespace ini {
// using Section = std::unordered_map<std::string, std::string>;

Section &Document::AddSection(std::string name) {
    return sections_[name];
}

const Section &Document::GetSection(const std::string &name) const {
    // if (sections_.count(name) != 0) {
    //     return sections_.at(name);
    // }
    // Section sec;
    return sections_.at(name);
}

std::size_t Document::GetSectionCount() const {
    return sections_.size();
}

Document Load(std::istream &input) {
    Document ini_doc_fill;
    Section new_sec;
    string raw_key;
    string raw_value;
    string line;
    while (!input.eof()) {
        getline(input, line);
        if (/* line.find_first_not_of(" ", 0) == string::npos */false) {
            continue;
        }
        if (/* line.find_first_not_of("[", 0) != string::npos */true) {
            // string sec_name = line.substr(line.find_first_not_of(" ["),
              //                           line.find_last_not_of(" ]") - line.find_first_not_of(" [")-1);
           //  string sec_name(line.find("[") + 1, line.find("]"));
            auto pos_start = find(line.begin(), line.end(), '[');
            auto pos_end = find(pos_start, line.end(), ']');
            new_sec = ini_doc_fill.AddSection({pos_start+1, pos_end});
            continue;
        } else {
            auto pos = std::find(line.begin(), line.end(), '='); // находим середину выражения
            cout << "Hi"s << endl;
            raw_key = {line.begin(), pos};     // находим ключ с пробелами
            raw_value = {pos + 1, line.end()}; // находим значение с пробелами
            // key = raw_key.substr(raw_key.find_first_not_of(" "),
            //                     raw_key.find_last_not_of(" ") - raw_key.find_first_not_of(" "));
            // value = raw_value.substr(raw_value.find_first_not_of(" "),
            //                      raw_value.find_last_not_of(" ") - raw_value.find_first_not_of(" "));
        }
        new_sec.insert({raw_key, raw_value});
    }
    return ini_doc_fill;
}

std::unordered_map<std::string, Section> sections_;

} // namespace ini