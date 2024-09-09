#define _USE_MATH_DEFINES
#include "svg.h"

#include <cmath>

using namespace std::literals;
using namespace svg;

namespace {
svg::Polyline CreateStar(svg::Point center, double outer_rad, double inner_rad, int num_rays) {
    using namespace svg;
    Polyline polyline;
    for (int i = 0; i <= num_rays; ++i) {
        double angle = 2 * M_PI * (i % num_rays) / num_rays;
        polyline.AddPoint({center.x + outer_rad * sin(angle), center.y - outer_rad * cos(angle)});
        if (i == num_rays) {
            break;
        }
        angle += M_PI / num_rays;
        polyline.AddPoint({center.x + inner_rad * sin(angle), center.y - inner_rad * cos(angle)});
    }
    return polyline;
}
} // namespace

namespace shapes {

class Triangle : public svg::Drawable {
public:
    Triangle(svg::Point p1, svg::Point p2, svg::Point p3)
        : p1_(p1), p2_(p2), p3_(p3) {
    }

    // Реализует метод Draw интерфейса svg::Drawable
    void Draw(svg::ObjectContainer &container) const override {
        container.Add(svg::Polyline().AddPoint(p1_).AddPoint(p2_).AddPoint(p3_).AddPoint(p1_));
    }

private:
    svg::Point p1_, p2_, p3_;
};

class Star : public svg::Drawable { /* Реализуйте самостоятельно */
public:
    Star(svg::Point p, double out_radius, double in_radius, int num_rays)
        : center_(p), outer_radius_(out_radius), inner_radius_(in_radius), num_rays_(num_rays) {};

    

    // method implementation
    void Draw(svg::ObjectContainer &container) const override {
        svg::Polyline star = CreateStar(center_, outer_radius_, inner_radius_, num_rays_);
        container.Add(star.SetFillColor("red"s).SetStrokeColor("black"));
    }

private:
    svg::Point center_;
    double outer_radius_;
    double inner_radius_;
    int num_rays_;
};

class Snowman : public svg::Drawable { /* Реализуйте самостоятельно */
public:
    Snowman(svg::Point p, double radius) : head_center_(p), head_radius_(radius) {};
    void Draw(svg::ObjectContainer &container) const override {
        container.Add(svg::Circle().SetCenter({head_center_.x, head_center_.y + 5 * head_radius_}).SetRadius(2 * head_radius_).SetFillColor("rgb(240,240,240)"s).SetStrokeColor("black"));
        container.Add(svg::Circle().SetCenter({head_center_.x, head_center_.y + 2 * head_radius_}).SetRadius(1.5 * head_radius_).SetFillColor("rgb(240,240,240)"s).SetStrokeColor("black"));
        container.Add(svg::Circle().SetCenter(head_center_).SetRadius(head_radius_).SetFillColor("rgb(240,240,240)"s).SetStrokeColor("black"));
    }

private:
    svg::Point head_center_;
    double head_radius_;
};

} // namespace shapes

template <typename DrawableIterator>
void DrawPicture(DrawableIterator begin, DrawableIterator end, svg::ObjectContainer &target) {
    for (auto it = begin; it != end; ++it) {
        (*it)->Draw(target);
    }
}

template <typename Container>
void DrawPicture(const Container &container, svg::ObjectContainer &target) {
    using namespace std;
    DrawPicture(begin(container), end(container), target);
}

uint8_t Lerp(uint8_t from, uint8_t to, double t) {
    return static_cast<uint8_t>(std::round((to - from) * t + from));
}

// Выполняет линейную интерполяцию Rgb цвета от from до to в зависимости от параметра t
svg::Rgb Lerp(svg::Rgb from, svg::Rgb to, double t) {
    return {Lerp(from.red, to.red, t), Lerp(from.green, to.green, t), Lerp(from.blue, to.blue, t)};
}

int main() {
    using namespace svg;
    using namespace std;

    Color none_color;
    cout << none_color << endl; // none
    
    Color purple{"purple"s};
    cout << purple << endl; // purple
    
    Color rgb = Rgb{100, 200, 255};
    cout << rgb << endl; // rgb(100,200,255)

    Color rgba = Rgba{100, 200, 255, 0.5};
    cout << rgba << endl; // rgba(100,200,255,0.5)

    Circle c;
    c.SetRadius(3.5).SetCenter({1.0, 2.0});
    c.SetFillColor(rgba);
    c.SetStrokeColor(purple);
    
    Document doc;
    doc.Add(std::move(c));
    doc.Render(cout);
} 