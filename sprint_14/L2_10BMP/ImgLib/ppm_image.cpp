#include "ppm_image.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

static const string_view PPM_SIG = "P6"sv;
static const int PPM_MAX = 255;

bool SavePPM(const Path &file, const Image &image) {
    ofstream out(file, ios::binary);

    out << PPM_SIG << '\n'
        << image.GetWidth() << ' ' << image.GetHeight() << '\n'
        << PPM_MAX << '\n';

    const int width = image.GetWidth();
    const int height = image.GetHeight();
    std::vector<char> buff(width * 3);

    for (int y = 0; y < height; ++y) {
        const Color *line = image.GetLine(y);
        for (int x = 0; x < width; ++x) {
            buff[x * 3 + 0] = static_cast<char>(line[x].r);
            buff[x * 3 + 1] = static_cast<char>(line[x].g);
            buff[x * 3 + 2] = static_cast<char>(line[x].b);
        }
        out.write(buff.data(), width * 3);
    }

    return out.good();
}

Image LoadPPM(const Path &file) {
    // открываем поток с флагом ios::binary
    // поскольку будем читать данные в двоичном формате
    ifstream ifs(file, ios::binary);
    if (!ifs.is_open()) {
        return {};
    }
    std::string sign;
    int width;
    int height;
    int color_max;

    // читаем заголовок: он содержит формат, размеры изображения
    // и максимальное значение цвета
    ifs >> sign >> width >> height >> color_max;

    // мы поддерживаем изображения только формата P6
    // с максимальным значением цвета 255
    if (sign != PPM_SIG || color_max != PPM_MAX) {
        return {};
    }

    // пропускаем один байт - это конец строки
    const char next = ifs.get();
    if (next != '\n') {
        return {};
    }

    Image result(width, height, Color::Black());
    std::vector<char> buff(width * 3);

    for (int y = 0; y < height; ++y) {
        Color *line = result.GetLine(y);
        ifs.read(buff.data(), width * 3);

        for (int x = 0; x < width; ++x) {
            line[x].r = static_cast<byte>(buff[x * 3 + 0]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].b = static_cast<byte>(buff[x * 3 + 2]);
        }
    }

    return result;
}

} // namespace img_lib