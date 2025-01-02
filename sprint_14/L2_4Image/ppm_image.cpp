#include "ppm_image.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

static const string_view PPM_SIG = "P6"sv;
static const int PPM_MAX = 255;

// реализуйте эту функцию самостоятельно
bool SavePPM(const Path &file, const Image &image) {
    std::ofstream ofs(file, ios::binary);
    if (!ofs.is_open()) {
        return {};
    }
    ofs << PPM_SIG << '\n';
    ofs << image.GetWidth() << ' ' << image.GetHeight() << '\n';
    ofs << PPM_MAX << '\n';
    std::vector<char> buff(image.GetWidth() * 3);
    // обработка строк
    for (int y = 0; y < image.GetHeight(); ++y) {
        const Color *line = image.GetLine(y);
        for (int x = 0; x < image.GetWidth(); ++x) {
            buff[x * 3 + 0] = static_cast<char>(line[x].r);
            buff[x * 3 + 1] = static_cast<char>(line[x].g);
            buff[x * 3 + 2] = static_cast<char>(line[x].b);
        }
        ofs.write(buff.data(), buff.size());
    }
    ofs.close();
    return true;
}

void NegateInplace(img_lib::Image &image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        Color *line = image.GetLine(y);
        for (int x = 0; x < image.GetWidth(); ++x) {
            line[x].r = static_cast<std::byte>(255 - std::to_integer<int>(line[x].r));
            line[x].g = static_cast<std::byte>(255 - std::to_integer<int>(line[x].g));
            line[x].b = static_cast<std::byte>(255 - std::to_integer<int>(line[x].b));
        }
    }
}

Image LoadPPM(const Path &file) {
    // открываем поток с флагом ios::binary
    // поскольку будем читать даные в двоичном формате
    ifstream ifs(file, ios::binary);
    std::string sign;
    int w, h, color_max;

    // читаем заголовок: он содержит формат, размеры изображения
    // и максимальное значение цвета
    ifs >> sign >> w >> h >> color_max;

    // мы поддерживаем изображения только формата P6
    // с максимальным значением цвета 255
    if (sign != PPM_SIG || color_max != PPM_MAX) {
        return {};
    }

    // пропускаем один байт - это конец строки
    const int next = ifs.get();
    if (next == EOF) {
        return {};
    }

    Image result(w, h, Color::Black());
    std::vector<char> buff(w * 3);

    for (int y = 0; y < h; ++y) {
        Color *line = result.GetLine(y);
        ifs.read(buff.data(), w * 3);

        for (int x = 0; x < w; ++x) {
            line[x].r = static_cast<byte>(buff[x * 3 + 0]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].b = static_cast<byte>(buff[x * 3 + 2]);
        }
    }

    return result;
}

} // namespace img_lib