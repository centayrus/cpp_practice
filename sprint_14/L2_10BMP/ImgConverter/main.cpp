#include <img_lib.h>
#include <jpeg_image.h>
#include <ppm_image.h>
#include <bmp_image.h>

#include <filesystem>
#include <iostream>
#include <memory>
#include <string_view>

using namespace std;

enum class Format {
    BMP,
    JPEG,
    PPM,
    UNKNOWN
};

class ImageFormatInterface {
public:
    virtual bool SaveImage(const img_lib::Path &file, const img_lib::Image &image) const = 0;
    virtual img_lib::Image LoadImage(const img_lib::Path &file) const = 0;
};

namespace interface {
class PPM : public ImageFormatInterface {
public:
    bool SaveImage(const img_lib::Path &file, const img_lib::Image &image) const override {
        return img_lib::SavePPM(file, image);
    }

    img_lib::Image LoadImage(const img_lib::Path &file) const override {
        return img_lib::LoadPPM(file);
    }
};

class JPEG : public ImageFormatInterface {
public:
    bool SaveImage(const img_lib::Path &file, const img_lib::Image &image) const override {
        return img_lib::SaveJPEG(file, image);
    }

    img_lib::Image LoadImage(const img_lib::Path &file) const override {
        return img_lib::LoadJPEG(file);
    }
};

class BMP : public ImageFormatInterface {
public:
    bool SaveImage(const img_lib::Path &file, const img_lib::Image &image) const override {
        return img_lib::SaveBMP(file, image);
    }

    img_lib::Image LoadImage(const img_lib::Path &file) const override {
        return img_lib::LoadBMP(file);
    }
};
} // namespace interface

Format GetFormatByExtension(const img_lib::Path &input_file) {
    const string ext = input_file.extension().string();
    if (ext == ".jpg"sv || ext == ".jpeg"sv) {
        return Format::JPEG;
    }

    if (ext == ".ppm"sv) {
        return Format::PPM;
    }

    if (ext == ".bmp"sv) {
        return Format::BMP;
    }
    return Format::UNKNOWN;
}

std::unique_ptr<ImageFormatInterface> GetFormatInterface(const img_lib::Path &path) {
    Format format = GetFormatByExtension(path);
    switch (format) {
    case Format::PPM:
        return std::make_unique<interface::PPM>();
        break;
    case Format::JPEG:
        return std::make_unique<interface::JPEG>();
        break;
    case Format::BMP:
        return std::make_unique<interface::BMP>();
        break;
    }
    return nullptr;
}

int main(int argc, const char **argv) {
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <in_file> <out_file>"sv << endl;
        return 1;
    }

    img_lib::Path in_path = argv[1];
    img_lib::Path out_path = argv[2];

    std::unique_ptr<ImageFormatInterface> in_img_interface = GetFormatInterface(in_path);
    if (!in_img_interface) {
        cerr << "Unknown format of the input file"sv << endl;
        return 2;
    }
    std::unique_ptr<ImageFormatInterface> out_img_interface = GetFormatInterface(out_path);
    if (!out_img_interface) {
        cerr << "Unknown format of the input file"sv << endl;
        return 3;
    }

    img_lib::Image image = in_img_interface->LoadImage(in_path);
    if (!image) {
        cerr << "Loading failed"sv << endl;
        return 4;
    }

    if (!out_img_interface->SaveImage(out_path, image)) {
        cerr << "Saving failed"sv << endl;
        return 5;
    }

    cout << "Successfully converted"sv << endl;
}