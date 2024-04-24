#include <algorithm>
#include <cassert>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

using Section = std::unordered_map<std::string, std::string>;

class Document {
public:
    // реализация методов должна быть в файле ini.cpp

    Section &AddSection(std::string name) {
        return sections_[name];
    }

    const Section &GetSection(const std::string &name) const {
        if (sections_.count(name) != 0) {
            return sections_.at(name);
        }
     //   std::unordered_map<std::string, std::string> sec;
     //Section s = {};
        auto s = std::pair<string, string>{};
        return s;
        
    }

    std::size_t GetSectionCount() const {
        return sections_.size();
    }

private:
    std::unordered_map<std::string, Section> sections_;
};

Document Load(std::istream &input) {
    Document ini_doc_fill;
    Section *new_sec;
    string raw_key, raw_value, key, value, line;
    while (!input.eof()) {
        getline(input, line);
        if (line.find_first_not_of(" ", 0) == string::npos) {
            continue;
        }
        if (line.find_first_of("[", 0) != string::npos) {
            // string sec_name = line.substr(line.find_first_not_of(" ["),
            //                           line.find_last_not_of(" ]") - line.find_first_not_of(" [")-1);
            //  string sec_name(line.find("[") + 1, line.find("]"));
            auto pos_start = find(line.begin(), line.end(), '[');
            auto pos_end = find(pos_start, line.end(), ']');
            new_sec = &ini_doc_fill.AddSection({pos_start + 1, pos_end});
            continue;
        } else {
            auto pos = std::find(line.begin(), line.end(), '='); // находим середину выражения
            cout << "Hi"s << endl;
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

int main() {
    std::istringstream input{
        "[vegetables]\n"
        "potatoes=10\n"
        "onions=1 \n"
        "\n"
        "cucumbers=12\n"
        "\n"
        "[guests] \n"
        "guest1_name = Ivan Durak\n"
        "guest2_name =  Vasilisa Premudraya\n"
        "[guest black list]"};
    Document doc = Load(input);

    assert(doc.GetSectionCount() == 3);
    auto i = doc.GetSection("vegetables"s);
    Section l{{"potatoes"s, "10"s},
              {"onions"s, "1"s},
              {"cucumbers"s, "12"s}};
    assert((doc.GetSection("vegetables"s) == Section{
                                                 {"potatoes"s, "10"s},
                                                 {"onions"s, "1"s},
                                                 {"cucumbers"s, "12"s}}));
    assert((doc.GetSection("guests"s) == Section{{"guest1_name"s, "Ivan Durak"s}, {"guest2_name"s, "Vasilisa Premudraya"s}}));
    assert((doc.GetSection("dragons"s) == Section{}));
    assert((doc.GetSection("guest black list"s) == Section{}));

    doc.AddSection("pets"s) = Section{{"nasty"s, "rat"s}};
    assert(doc.GetSectionCount() == 4);
}