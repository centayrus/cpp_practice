#include <cassert>
#include <deque>
#include <map>
#include <string>
#include <string_view>

using namespace std;
class Translator {

public:
    Translator() = default;

    void Add(std::string_view source, std::string_view target) {
        dict_word_.push_back(string{source});
        auto src = dict_word_.back().data();
        dict_word_.push_back(string{target});
        auto trg = dict_word_.back().data();
        forward_dict_[src] = trg;
        backward_dict_[trg] = src;
    }

    std::string_view TranslateForward(std::string_view source) const {
        if (forward_dict_.count(source)) {
            return forward_dict_.at(source);
        }
        return ""sv;
    }

    std::string_view TranslateBackward(std::string_view target) const {
        if (backward_dict_.count(target)) {
            return backward_dict_.at(target);
        }
        return ""sv;
    }

private:
    std::map<std::string_view, std::string_view> forward_dict_ = {};
    std::map<std::string_view, std::string_view> backward_dict_ = {};
    std::deque<std::string> dict_word_ = {};
};

void TestSimple() {
    Translator translator;
    translator.Add(string{"okno"s}, string{"window"s});
    translator.Add(string("stol"s), string("table"s));

    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
    translator.Add(string("stol"s), string("able"s));
    assert(translator.TranslateForward("stol"s) == "able"s);
}

int main() {
    TestSimple();
}
