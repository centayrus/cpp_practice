#include "ini.h"

using namespace std;

namespace ini {

Section &Document::AddSection(std::string name) {
    return sections_[name];
}

const Section &Document::GetSection(const std::string &name) const {
    if (sections_.count(name) != 0) {
        return sections_.at(name);
    }
    return null_sec_;
}

std::size_t Document::GetSectionCount() const {
    return sections_.size();
}

Document Load(std::istream &input) {
    Document ini_doc_fill;
    Section *new_sec = nullptr;
    string raw_key, raw_value, key, value, line;
    while (!input.eof()) {
        getline(input, line);
        if (line.find_first_not_of(" ", 0) == string::npos) {
            continue;
        }
        if (line.find_first_of("[", 0) != string::npos) {
            auto pos_start = find(line.begin(), line.end(), '[');
            auto pos_end = find(pos_start, line.end(), ']');
            new_sec = &ini_doc_fill.AddSection({pos_start + 1, pos_end});
            continue;
        } else {
            auto pos = std::find(line.begin(), line.end(), '='); // находим середину выражения
            raw_key = {line.begin(), pos};     // находим ключ с пробелами
            raw_value = {pos + 1, line.end()}; // находим значение с пробелами
            key = raw_key.substr(raw_key.find_first_not_of(" "),
                                 raw_key.find_last_not_of(" ") - raw_key.find_first_not_of(" ") + 1);
            value = raw_value.substr(raw_value.find_first_not_of(" "),
                                     raw_value.find_last_not_of(" ") - raw_value.find_first_not_of(" ") + 1);
        }
        new_sec->insert({move(key), move(value)});
    }
    return ini_doc_fill;
}

std::unordered_map<std::string, Section> sections_;

} // namespace ini