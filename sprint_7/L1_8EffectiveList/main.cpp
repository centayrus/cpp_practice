#include <iostream>
#include <iterator>
#include <list>
#include <string>

using namespace std;

class Editor {
public:
    Editor() = default;

    // сдвинуть курсор влево
    void Left() {
        --pos_;
    }

    // сдвинуть курсор вправо
    void Right() {
        if (pos_ != text_.end()) {
            ++pos_;
        }
    }

    // вставить символ token
    void Insert(char token) {
        text_.insert(pos_, token);
    }

    // вырезать не более tokens символов, начиная с текущей позиции курсора
    void Cut(size_t tokens = 1) {
        buffer_.erase(buffer_.begin(), buffer_.end());
        if (static_cast<size_t>(std::distance(pos_, text_.end())) < tokens) {
            tokens = std::distance(pos_, text_.end());
        }
        for (size_t i = 0; i < tokens; ++i) {
            buffer_.push_back(*pos_);
            ++pos_;
        }
       text_.erase(std::next(pos_, -tokens), pos_);
    }

    // cкопировать не более tokens символов, начиная с текущей позиции курсора
    void Copy(size_t tokens = 1) {
        buffer_.erase(buffer_.begin(), buffer_.end());
        auto it = pos_;
        if (static_cast<size_t>(std::distance(pos_, text_.end())) < tokens) {
            tokens = std::distance(pos_, text_.end());
        }
        for (size_t i = 0; i < tokens; ++i) {
            buffer_.push_back(*pos_);
            ++pos_;
        }
        pos_ = it;
    }

    // вставить содержимое буфера в текущую позицию курсора
    void Paste() {
        for (auto c : buffer_) {
            text_.insert(pos_, c);
           
        }
    }

    // получить текущее содержимое текстового редактора
    std::string GetText() const {
        std::string expr;
        for (auto c : text_) {
            expr += c;
        }
        return expr;
    }

private:
    std::list<char> text_ = {};
    std::list<char> buffer_ = {};
    std::list<char>::iterator pos_ = text_.begin();
};

int main() {
    Editor editor;
    const std::string text = "hello, world"s;
    for (char c : text) {
        editor.Insert(c);
    }
    // Текущее состояние редактора: `hello, world|`
    for (size_t i = 0; i < text.size(); ++i) {
        editor.Left();
    }
    // Текущее состояние редактора: `|hello, world`
    editor.Cut(7);
    // Текущее состояние редактора: `|world`
    // в буфере обмена находится текст `hello, `
    for (size_t i = 0; i < 5; ++i) {
        editor.Right();
    }
    // Текущее состояние редактора: `world|`
    editor.Insert(',');
    editor.Insert(' ');
    // Текущее состояние редактора: `world, |`
    editor.Paste();
    // Текущее состояние редактора: `world, hello, |`
    editor.Left();
    editor.Left();
    // Текущее состояние редактора: `world, hello|, `
    editor.Cut(3); // Будут вырезаны 2 символа
    // Текущее состояние редактора: `world, hello|`
    std::cout << editor.GetText();
    return 0;
}



// авторский вариант. Элегантный, в отличие от куска говна, что выше
/* #include <iostream>
#include <list>
#include <string>



using namespace std;

class Editor {
public:
    Editor()
            : pos(text.end()) {
    }

    void Left() {
        pos = Advance(pos, -1);
    }

    void Right() {
        pos = Advance(pos, 1);
    }

    void Insert(char token) {
        text.insert(pos, token);
    }

    void Cut(size_t tokens = 1) {
        auto pos2 = Advance(pos, tokens);
        buffer.assign(pos, pos2);
        pos = text.erase(pos, pos2);
    }

    void Copy(size_t tokens = 1) {
        auto pos2 = Advance(pos, tokens);
        buffer.assign(pos, pos2);
    }

    void Paste() {
        text.insert(pos, buffer.begin(), buffer.end());
    }

    string GetText() const {
        return {text.begin(), text.end()};
    }

private:
    using Iterator = list<char>::iterator;
    list<char> text;
    list<char> buffer;
    Iterator pos;

    Iterator Advance(Iterator it, int steps) const {
        while (steps > 0 && it != text.end()) {
            ++it;
            --steps;
        }
        while (steps < 0 && it != text.begin()) {
            --it;
            ++steps;
        }
        return it;
    }
}; */