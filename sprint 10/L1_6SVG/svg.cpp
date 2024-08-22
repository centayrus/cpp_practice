#include "svg.h"

#include <iomanip>

namespace svg {

using namespace std::literals;

void Object::Render(const RenderContext &context) const {
    context.RenderIndent();

    // Делегируем вывод тега своим подклассам
    RenderObject(context);

    context.out << std::endl;
}

// ---------- Circle ------------------

Circle &Circle::SetCenter(Point center) {
    center_ = std::move(center);
    return *this;
}

Circle &Circle::SetRadius(double radius) {
    radius_ = std::move(radius);
    return *this;
}

void Circle::RenderObject(const RenderContext &context) const {
    auto &out = context.out;
    out << "<circle cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
    out << "r=\""sv << radius_ << "\" "sv;
    out << "/>"sv;
}
// ---------- End Circle ------------------

// ---------- Polyline ------------------
Polyline &Polyline::AddPoint(Point point) {
    // line_points_.emplace_back(point.x);
    line_points_.emplace_back(point);
    return *this;
}

void Polyline::RenderObject(const RenderContext &context) const {
    auto &out = context.out;
    //std::string point_line = ""s;
    bool first = true;
    out << "<polyline points=\""sv;
    for (auto dot : line_points_) {
        if (!first) {
            //point_line += ' ';
            out << ' ';
        }
        first = false;
       // point_line += std::to_string(dot.x);
       out << dot.x;
       // point_line += ',';
       out << ","sv;
       // point_line += std::to_string(dot.y);
       out << dot.y;
    }
    //out << "<polyline points=\""sv << point_line << "\" />"sv;
    out << "\" />"sv;
}

// ---------- End Polyline ------------------

// ---------- Text ------------------
Text &Text::SetPosition(Point pos) {
    pos_ = pos;
    return *this;
}

Text &Text::SetOffset(Point offset) {
    offset_ = offset;
    return *this;
}

Text &Text::SetFontSize(uint32_t size) {
    size_ = size;
    return *this;
}

Text &Text::SetFontFamily(std::string font_family) {
    font_family_ = font_family;
    return *this;
}

Text &Text::SetFontWeight(std::string font_weight) {
    font_weight_ = font_weight;
    return *this;
}

Text &Text::SetData(std::string data) {
    data_ = data;
    return *this;
}

void Text::RenderObject(const RenderContext &context) const {
    auto &out = context.out;
   // std::string modified_data = ""s;
   out << "<text x=\""sv << pos_.x << "\" y=\""sv << pos_.y << "\" "sv;
out << "dx=\""sv << offset_.x << "\" dy=\""sv << offset_.y << "\" "sv;
out << "font-size=\""sv << size_ << "\" font-family=\""sv << font_family_ << "\" "sv;
out << "font-weight=\""sv << font_weight_ << "\">"sv;
    for (char c : data_) {
        switch (c) {
        case '"':
            //modified_data += "&quot;";
            out << "&quot;"sv;
            break;
        case '\'':
            //modified_data += "&apos;";
            out << "&apos;"sv;
            break;
        case '<':
            //modified_data += "&lt;";
            out << "&lt;"sv;
            break;
        case '>':
            //modified_data += "&gt;";
            out << "&gt;"sv;
            break;
        case '&':
            //modified_data += "&amp;";
            out << "&amp;"sv;
            break;
        default:
            //modified_data += c;
            out << c;
        }
    }


// out << modified_data 
out << "</text>"sv;
}


// ---------- End Text ------------------

// ---------- Document ------------------
/* template <typename Object>
void Document::Add(Object object) {
    objects_ptr_.emplace_back(std::make_unique<Object>(std::move(&object)));
} */

void Document::AddPtr(std::unique_ptr<Object> &&obj) {
    objects_ptr_.emplace_back(std::move(obj));
}

void Document::Render(std::ostream &out) const {
    std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"sv << std::endl;
    std::cout << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"sv << std::endl;
    for (const auto &object : objects_ptr_) {
        object->Render(out);
    }
    std::cout << "</svg>"sv;
}
// ---------- End Document ------------------

} // namespace svg
