#pragma once
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "geom.h"

class Tile {
public:
    // Размер тайла 8*8 пикселей.
    constexpr static int SIZE = 8;

    // Конструктор по умолчанию. Заполняет тайл указанным цветом.
    Tile(char color = ' ') noexcept {
        /* Реализуйте недостающий код самостоятельно. */
        tile_image_.reserve(SIZE);
        std::string line(SIZE, color);
        //std::cout << line << std::endl;
        for (int i = 0; i < SIZE; ++i) {
            tile_image_.push_back(line);
        }
        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    Tile(const Tile& other) {
        /* Реализуйте недостающий код самостоятельно. */
        tile_image_ = other.tile_image_;
        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    ~Tile() {
        // -------------- Не удалять ------------
        --instance_count_;  // Уменьшаем счётчик тайлов.
        assert(instance_count_ >= 0);
        // -------------- не удалять ------------
    }

    /**
     * Изменяет цвет пикселя тайла.
     * Если координаты выходят за пределы тайла, метод ничего не делает.
     */
    void SetPixel(Point p, char color) noexcept {
        /* Реализуйте недостающий код самостоятельно. */
         if (!(p.y >= SIZE || p.x >= SIZE || p.y < 0 || p.x < 0)) {
        tile_image_[p.y][p.x] = color;
         }
    }

    /**
     * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
     */
    char GetPixel(Point p) const noexcept {
        /* Реализуйте недостающий функционал самостоятельно. */
        if (p.y >= SIZE || p.x >= SIZE || p.y < 0 || p.x < 0) {return ' ';}
        return tile_image_[p.y][p.x];
    }

    // Возвращает количество экземпляра класса Tile в программе.
    static int GetInstanceCount() noexcept {
        // -------------- не удалять ------------
        return instance_count_;
        // -------------- не удалять ------------
    }

private:
    // -------------- не удалять ------------
    inline static int instance_count_ = 0;
    // -------------- не удалять ------------

    /* Разместите здесь поля для хранения пикселей тайла. */
    std::vector<std::string> tile_image_;
};