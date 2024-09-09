#include "json.h"

using namespace std;

namespace json {

namespace {

Node LoadNode(istream &input);

Node LoadArray(istream &input) {
    Array result;

    for (char c; input >> c && c != ']';) {
        if (c != ',') {
            input.putback(c);
        }
        result.push_back(LoadNode(input));
    }

    return Node(move(result));
}

Node LoadInt(istream &input) {
    int result = 0;
    while (isdigit(input.peek())) {
        result *= 10;
        result += input.get() - '0';
    }
    return Node(result);
}

Node LoadString(istream &input) {
    string line;
    getline(input, line, '"');
    return Node(std::move(line));
}

Node LoadDict(istream &input) {
    Dict result;

    for (char c; input >> c && c != '}';) {
        if (c == ',') {
            input >> c;
        }

        string key = LoadString(input).AsString();
        input >> c;
        result.insert({move(key), LoadNode(input)});
    }

    return Node(move(result));
}

Node LoadNode(istream &input) {
    char c;
    input >> c;

    if (c == '[') {
        return LoadArray(input);
    } else if (c == '{') {
        return LoadDict(input);
    } else if (c == '"') {
        return LoadString(input);
    } else {
        input.putback(c);
        return LoadInt(input);
    }
}

} // namespace
Node::Node() {}

Node::Node(int value)
    : value_(value) {
}

Node::Node(bool value)
    : value_(value) {
}

Node::Node(double value)
    : value_(value) {
}

Node::Node(std::string value)
    : value_(move(value)) {
}

Node::Node(Array array)
    : value_(move(array)) {
}

Node::Node(Dict map)
    : value_(move(map)) {
}

int Node::AsInt() const {
    if (!(IsInt())) {
        throw std::logic_error(""s);
    }
    return std::get<int>(value_);
}

bool Node::AsBool() const {
    if (!(IsBool())) {
        throw std::logic_error(""s);
    }
    return std::get<bool>(value_);
}

double Node::AsDouble() const {
    if (IsInt()) {
        return static_cast<double>(std::get<int>(value_));
    } else if (!(IsDouble())) {
        throw std::logic_error(""s);
    }
    return std::get<double>(value_);
}

const string &Node::AsString() const {
    if (!(IsString())) {
        throw std::logic_error(""s);
    }
    return std::get<std::string>(value_);
}

const Array &Node::AsArray() const {
    if ((IsArray())) {
        throw std::logic_error(""s);
    }
    return std::get<json::Array>(value_);
}

const Dict &Node::AsMap() const {
    if (!(IsMap())) {
        throw std::logic_error(""s);
    }
    return std::get<json::Dict>(value_);
}

bool Node::IsInt() const {
    return std::holds_alternative<int>(value_);
}

bool Node::IsDouble() const {
    return std::holds_alternative<int>(value_) || std::holds_alternative<double>(value_);
}

bool Node::IsPureDouble() const {
    return std::holds_alternative<double>(value_);
}

bool Node::IsBool() const {
    return std::holds_alternative<bool>(value_);
}

bool Node::IsString() const {
    return std::holds_alternative<std::string>(value_);
}

bool Node::IsNull() const {
    return std::holds_alternative<std::nullptr_t>(value_);
}

bool Node::IsArray() const {
    return std::holds_alternative<json::Array>(value_);
}

bool Node::IsMap() const {
    return std::holds_alternative<json::Dict>(value_);
}

Document::Document(Node root)
    : root_(move(root)) {
}

 const Node::Value &Node::GetValue() const {
    return value_; 
} 

const Node &Document::GetRoot() const {
    return root_;
}

Document Load(istream &input) {
    return Document{LoadNode(input)};
}

void Print(const Document &doc, std::ostream &output) {
    (void)&doc;
    (void)&output;
    PrintNode(doc.GetRoot(), output);
    // Реализуйте функцию самостоятельно
}

bool operator==(const json::Node &node1,const json::Node& node2) {
    return (node1.AsInt() == node2.AsInt() ||
    node1.AsBool() == node2.AsBool() ||
    node1.AsDouble() == node2.AsDouble() ||
    node1.AsString() == node2.AsString() ||
    node1.AsArray() == node2.AsArray() ||
    node1.AsMap() == node2.AsMap()) &&
    (node1.IsInt() == node2.IsInt() ||
    node1.IsBool() == node2.IsBool() ||
    node1.IsDouble() == node2.IsDouble() ||
    node1.IsString() == node2.IsString() ||
    node1.IsArray() == node2.IsArray() ||
    node1.IsMap() == node2.IsMap());
}

bool operator!=(const json::Node &node1,const json::Node& node2) {
    return (node1.AsInt() != node2.AsInt() ||
    node1.AsBool() != node2.AsBool() ||
    node1.AsDouble() != node2.AsDouble() ||
    node1.AsString() != node2.AsString() ||
    node1.AsArray() != node2.AsArray() ||
    node1.AsMap() != node2.AsMap()) ||
    (node1.IsInt() != node2.IsInt() ||
    node1.IsBool() != node2.IsBool() ||
    node1.IsDouble() != node2.IsDouble() ||
    node1.IsString() != node2.IsString() ||
    node1.IsArray() != node2.IsArray() ||
    node1.IsMap() != node2.IsMap());
}

} // namespace json