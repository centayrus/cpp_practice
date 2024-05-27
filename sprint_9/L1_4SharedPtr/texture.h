#pragma once
#include "common.h"

class Texture {
public:
    explicit Texture(Image image)
        : image_(std::move(image)) {
    }

    Size GetSize() const {
        // Заглушка. Реализуйте метод самостоятельно
        int width = image_[0].size();
        int height = image_.size();
        return {width, height};
       //return GetImageSize(image_);
    }

    char GetPixelColor(Point p) const {
        //(void) p;
        // Заглушка. Реализуйте метод самостоятельно
        return image_[p.y][p.x];
    }

private:
    Image image_ = {};
};