#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std::literals;
namespace svg {

struct Point {
    Point() = default;
    Point(double x1, double y1)
        : x(x1), y(y1) {
    }
    double x = 0;
    double y = 0;
};

/*
 * Вспомогательная структура, хранящая контекст для вывода SVG-документа с отступами.
 * Хранит ссылку на поток вывода, текущее значение и шаг отступа при выводе элемента
 */
struct RenderContext {
    RenderContext(std::ostream &out1)
        : out(out1) {
    }

    RenderContext(std::ostream &out1, int indent_step1, int indent1 = 0)
        : out(out1), indent_step(indent_step1), indent(indent1) {
    }

    RenderContext Indented() const {
        return {out, indent_step, indent + indent_step};
    }

    void RenderIndent() const {
        for (int i = 0; i < indent; ++i) {
            out.put(' ');
        }
    }

    std::ostream &out;
    int indent_step = 0;
    int indent = 0;
};

/*
 * Абстрактный базовый класс Object служит для унифицированного хранения
 * конкретных тегов SVG-документа
 * Реализует паттерн "Шаблонный метод" для вывода содержимого тега
 */
class Object {
public:
    void Render(const RenderContext& context) const;

    virtual ~Object() = default;

private:
    virtual void RenderObject(const RenderContext& context) const = 0;
};

/*
 * Класс Circle моделирует элемент <circle> для отображения круга
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/circle
 */
class Circle final : public Object {
public:
    Circle() = default;
    Circle &SetCenter(Point center);
    Circle &SetRadius(double radius);

private:
    void RenderObject(const RenderContext &context) const override;

    Point center_ = {0.0, 0.0};
    double radius_ = 1.0;
};

/*
 * Класс Polyline моделирует элемент <polyline> для отображения ломаных линий
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/polyline
 */
class Polyline : public Object {
public:
    Polyline() = default;
    // Добавляет очередную вершину к ломаной линии
    Polyline &AddPoint(Point point);

    /*
     * Прочие методы и данные, необходимые для реализации элемента <polyline>
     */
private:
    void RenderObject(const RenderContext &context) const override;

    std::vector<Point> line_points_;
};

/*
 * Класс Text моделирует элемент <text> для отображения текста
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/text
 */
class Text : public Object {
public:
    Text() = default;
    // Задаёт координаты опорной точки (атрибуты x и y)
    Text &SetPosition(Point pos);

    // Задаёт смещение относительно опорной точки (атрибуты dx, dy)
    Text &SetOffset(Point offset);

    // Задаёт размеры шрифта (атрибут font-size)
    Text &SetFontSize(uint32_t size);

    // Задаёт название шрифта (атрибут font-family)
    Text &SetFontFamily(std::string font_family);

    // Задаёт толщину шрифта (атрибут font-weight)
    Text &SetFontWeight(std::string font_weight);

    // Задаёт текстовое содержимое объекта (отображается внутри тега text)
    Text &SetData(std::string data);

    // Прочие данные и методы, необходимые для реализации элемента <text>
private:
    void RenderObject(const RenderContext &context) const override;

    Point pos_ = {0.0, 0.0};
    Point offset_ = {0.0, 0.0};
    uint32_t size_ = 1;
    std::string font_family_ = ""s;
    std::string font_weight_ = ""s;
    std::string data_ = ""s;
};

class Document {
public:
    /*
     Метод Add добавляет в svg-документ любой объект-наследник svg::Object.
     Пример использования:
     Document doc;
     doc.Add(Circle().SetCenter({20, 30}).SetRadius(15));
    */
    template <typename Object>
    void Add(Object object);

    // Добавляет в svg-документ объект-наследник svg::Object
    void AddPtr(std::unique_ptr<svg::Object> &&obj);

    // Выводит в ostream svg-представление документа
    void Render(std::ostream &out) const;

    // Прочие методы и данные, необходимые для реализации класса Document

private:
    std::vector<std::unique_ptr<Object>> objects_ptr_;
};

template <typename Object>
void Document::Add(Object object) {
    objects_ptr_.emplace_back(std::make_unique<Object>(std::move(object)));
}

} // namespace svg