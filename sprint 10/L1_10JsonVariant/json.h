#pragma once

#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

using namespace std::literals;

namespace json {

class Node;
// Сохраните объявления Dict и Array без изменения
using Dict = std::map<std::string, Node>;
using Array = std::vector<Node>;

// Эта ошибка должна выбрасываться при ошибках парсинга JSON
class ParsingError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class Node {
public:
    using Value = std::variant<std::nullptr_t, int, double, std::string, bool, Array, Dict>;
    /* Реализуйте Node, используя std::variant */

    explicit Node(Array array);
    explicit Node(Dict map);
    explicit Node(int value);
    explicit Node(std::string value);
    explicit Node(bool is_yn);
    explicit Node(double value);

    int AsInt() const;
    bool AsBool() const;
    double AsDouble() const; // Возвращает значение типа double, если внутри хранится double либо int.
                             // В последнем случае возвращается приведённое в double значение.
    const std::string &AsString() const;
    const Array &AsArray() const;
    const Dict &AsMap() const;

    bool IsInt() const;
    bool IsDouble() const;     // Возвращает true, если в Node хранится int либо double.
    bool IsPureDouble() const; // Возвращает true, если в Node хранится double.
    bool IsBool() const;
    bool IsString() const;
    bool IsNull() const;
    bool IsArray() const;
    bool IsMap() const;

    const Value &GetValue() const {
        return value_;
    }

private:
    Value value_;
};

std::ostream &operator<<(std::ostream &out, const Node &node);

// Шаблон, подходящий для вывода double и int
template <typename Value>
void PrintValue(const Value &value, std::ostream &out) {
    out << value;
}

// Перегрузка функции PrintValue для вывода значений null
void PrintValue(std::nullptr_t, std::ostream &out) {
    out << "null"sv;
}

// Перегрузка функции PrintValue для вывода Array
void PrintValue(Array array, std::ostream &out) {
    bool is_first = true;
    for (const auto &item : array) {
        if (!is_first) {
            out << ",";
        }
        out << item;
        is_first = false;
    }
}

void PrintValue(Dict dict, std::ostream &out) {
    bool is_first = true;
    for (const auto &item : dict) {
        if (!is_first) {
            out << ",";
        }
        out << item.first << ": " << item.second;
        is_first = false;
    }
}

void PrintValue(bool b, std::ostream &out) {
    out << std::boolalpha << b;
}

// void PrintValue(std::string& str, std::ostream& out) {
//     out << str;
// }

void PrintNode(const Node &node, std::ostream &out) {
    std::visit(
        [&out](const auto &value) { PrintValue(value, out); },
        node.GetValue());
}

class Document {
public:
    explicit Document(Node root);

    const Node &GetRoot() const;

private:
    Node root_;
};

Document Load(std::istream &input);

void Print(const Document &doc, std::ostream &output);

} // namespace json