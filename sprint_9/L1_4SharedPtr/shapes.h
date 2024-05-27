#pragma once
#include "texture.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

// Поддерживаемые виды фигур: прямоугольник и эллипс
enum class ShapeType { RECTANGLE,
                       ELLIPSE };

class Shape {
public:
    // Фигура после создания имеет нулевые координаты и размер,
    // а также не имеет текстуры
    explicit Shape(ShapeType type) {
        type_ = type;
    }

    void SetPosition(Point pos) {
        pos_ = pos;
    }

    void SetSize(Size size) {
        size_ = size;
    }

    void SetTexture(std::shared_ptr<Texture> texture) {
        texture_ = texture;
    }

    // Рисует фигуру на указанном изображении
    // В зависимости от типа фигуры должен рисоваться либо эллипс, либо прямоугольник
    // Пиксели фигуры, выходящие за пределы текстуры, а также в случае, когда текстура не задана,
    // должны отображаться с помощью символа точка '.'
    // Части фигуры, выходящие за границы объекта image, должны отбрасываться.
    void Draw(Image &image) const {
        int y = pos_.y;
        int x = pos_.x;
        char color;
        for (int i = 0; i < size_.height; ++i) {
            if (y > static_cast<int>(image.size())) {
                break;
            } else if (y < 0) {
                continue;
                ++y;
            }
            for (int j = 0; j < size_.width; ++j) {
                if (x > static_cast<int>(image[0].size())) {
                    break;
                } else if (x < 0) {
                    ++x;
                    continue;
                }
                if (texture_ == nullptr || j >= texture_->GetSize().width || i >= texture_->GetSize().height) {
                    color = '.';
                    if (type_ == ShapeType::ELLIPSE) {
                        if (!IsPointInEllipse({j, i}, size_)) {
                            ++x;
                            continue;
                        }
                    } else if (type_ == ShapeType::RECTANGLE) {
                        if (!IsPointInRectangle({j, i}, size_)) {
                            ++x;
                            continue;
                        }
                    }
                } else {
                    color = texture_->GetPixelColor({j, i});
                    if (type_ == ShapeType::ELLIPSE) {
                        if (!IsPointInEllipse({j, i}, size_)) {
                            ++x;
                            continue;
                        }
                    } else if (type_ == ShapeType::RECTANGLE) {
                        if (!IsPointInRectangle({j, i}, size_)) {
                            ++x;
                            continue;
                        }
                    }
                }
                image[y][x] = color;
                ++x;
            }
            x = pos_.x;
            ++y;
        }
    }

private:
    ShapeType type_;
    Point pos_;
    Size size_;
    std::shared_ptr<Texture> texture_;
};