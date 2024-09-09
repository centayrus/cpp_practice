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

    explicit Node();
    explicit Node(int value);
    explicit Node(bool is_yn);
    explicit Node(double value);
    explicit Node(std::string value);
    explicit Node(Array array);
    explicit Node(Dict map);

    int AsInt() const;
    bool AsBool() const;
    double AsDouble() const; // Возвращает значение типа double, если внутри хранится double либо int.
                             // В последнем случае возвращается приведённое в double значение.
    const std::string &AsString() const;
    const Array &AsArray() const;
    const Dict &AsMap() const;

    bool IsNull() const;
    bool IsInt() const;
    bool IsBool() const;
    bool IsDouble() const;     // Возвращает true, если в Node хранится int либо double.
    bool IsPureDouble() const; // Возвращает true, если в Node хранится double.
    bool IsString() const;
    bool IsArray() const;
    bool IsMap() const;

    const Value &GetValue() const;

private:
    Value value_;
};



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
        out << PrintValue(item.GetValue(), out);;
        is_first = false;
    }
}

void PrintValue(Dict dict, std::ostream &out) {
    bool is_first = true;
    for (const auto &item : dict) {
        if (!is_first) {
            out << ",";
        }
        out << item.first << ": " << PrintValue(item.second.GetValue(), out);
        is_first = false;
    }
}

void PrintValue(bool b, std::ostream &out) {
    out << std::boolalpha << b;
}

void PrintNode(const Node &node, std::ostream &out) {
    std::ostringstream strm;
    std::visit(
        [&strm](const auto &value) { PrintValue(value, strm); },
        node.GetValue());
        out << strm.str();
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

bool operator==(const json::Node &node1, const json::Node& node2);

bool operator!=(const json::Node &node1, const json::Node& node2);

} // namespace json