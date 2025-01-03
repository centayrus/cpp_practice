#include "bmp_image.h"
#include "pack_defines.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

// функция вычисления отступа по ширине
static int GetBMPStride(int width) {
    return 4 * ((width * 3 + 3) / 4);
}

PACKED_STRUCT_BEGIN BitmapFileHeader {
    // поля заголовка Bitmap File Header
    BitmapFileHeader(int width, int height) {

        bfSize = GetBMPStride(width) * height + 54;
    }
    uint16_t bfType = 0x4D42;     // Тип файла (должен быть 'BM' = 0x4D42)
    uint32_t bfSize = 0;          // Суммарный размер заголовка и данных - отступ, умноженный на высоту
    uint32_t bfReserved = 0;      // Зарезервировано (должно быть 0)
    uint32_t bfOffBits = 14 + 40; // Смещение к началу данных изображения
}
PACKED_STRUCT_END

PACKED_STRUCT_BEGIN BitmapInfoHeader {
    // поля заголовка Bitmap Info Header
    BitmapInfoHeader(int width, int height) : biWidth(width), biHeight(height) {
        biSizeImage = GetBMPStride(width) * height;
    }
    uint32_t biSize = 40;                // Размер структуры (должен быть 40 для BITMAPINFOHEADER)
    int32_t biWidth = 0;                 // Ширина изображения в пикселях
    int32_t biHeight = 0;                // Высота изображения в пикселях
    uint16_t biPlanes = 1;               // Количество цветовых плоскостей (должно быть 1)
    uint16_t biBitCount = 24;            // Глубина цвета (1, 4, 8, 16, 24, или 32)
    uint32_t biCompression = 0;          // Тип сжатия (0 - BI_RGB, без сжатия)
    uint32_t biSizeImage = 0;            // Размер изображения в байтах (может быть 0 для BI_RGB)
    int32_t biXPelsPerMeter = 11811;     // Горизонтальное разрешение в пикселях на метр
    int32_t biYPelsPerMeter = 11811;     // Вертикальное разрешение в пикселях на метр
    uint32_t biClrUsed = 0;              // Количество цветов в таблице (0 для всех цветов)
    uint32_t biClrImportant = 0x1000000; // Количество важнейших цветов (0 для всех цветов)
}
PACKED_STRUCT_END

// напишите эту функцию
bool SaveBMP(const Path &file, const Image &image) {
    ofstream out(file, ios::binary);
    if (!out.is_open()) {
        return false; // Не удалось открыть файл
    }
    const int width = image.GetWidth();
    const int height = image.GetHeight();
    BitmapFileHeader bfh{width, height};
    BitmapInfoHeader bih{width, height};
    out.write(reinterpret_cast<const char *>(&bfh), sizeof(bfh));
    out.write(reinterpret_cast<const char *>(&bih), sizeof(bih));
    const int indent = GetBMPStride(width);
    std::vector<char> buff(indent, 0);
    for (int y = height - 1; y >= 0; --y) {
        const Color *line = image.GetLine(y);
        for (int x = 0; x < width; ++x) {
            buff[x * 3 + 2] = static_cast<char>(line[x].r);
            buff[x * 3 + 1] = static_cast<char>(line[x].g);
            buff[x * 3 + 0] = static_cast<char>(line[x].b);
        }
        out.write(buff.data(), indent);
    }
    return out.good();
}

// напишите эту функцию
Image LoadBMP(const Path &file) {
    // открываем поток с флагом ios::binary поскольку будем читать данные в двоичном формате
    ifstream ifs(file, ios::binary);
    if (!ifs.is_open()) {
        return {}; // Не удалось открыть файл
    }
    uint16_t img_type;
    // читаем первые два байта для идентификации типа
    ifs.read(reinterpret_cast<char *>(&img_type), 2);
    if (img_type != 0x4D42) {
        return {};
    }
    int width;
    int height;
    ifs.seekg(18, std::ios::beg);
    ifs.read(reinterpret_cast<char *>(&width), sizeof(width));
    ifs.read(reinterpret_cast<char *>(&height), sizeof(height));
    BitmapFileHeader bfh(width, height);
    Image result(width, height, Color::Black());
    int indent = GetBMPStride(width);
    std::vector<char> buff(indent);
    ifs.seekg(bfh.bfOffBits, std::ios::beg);
    for (int y = height - 1; y >= 0; --y) {
        Color *line = result.GetLine(y);
        ifs.read(buff.data(), indent);
        for (int x = 0; x < width; ++x) {
            line[x].r = static_cast<byte>(buff[x * 3 + 2]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].b = static_cast<byte>(buff[x * 3 + 0]);
        }
    }
    return result;
}

} // namespace img_lib