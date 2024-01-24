#include "log_duration.h"

#include <fstream>
#include <iostream>
#include <random>
#include <string>

using namespace std;

size_t ReadExact(istream& input, char* dst, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        int c = input.get();
        if (c == istream::traits_type::eof() || !input) {
            return i;
        }
        dst[i] = static_cast<char>(c);
    }

    return count;
}

string GenerateRandomString(size_t size) {
    string random_str(size, 0);
    static mt19937 engine;

    for (char& c : random_str) {
        c = static_cast<char>(uniform_int_distribution<int>('A', 'Z')(engine));
    }

    return random_str;
}

int main() {
    // размер файла 10 мегабайт
    static const int FILE_SIZE = 10 * 1024 * 1024;
    static const int READ_COUNT = 10;

    // создаём файл нужного размера
    {
        ofstream test_out("test.txt");
        test_out << GenerateRandomString(FILE_SIZE);
    }

    vector<char> buffer(FILE_SIZE);

    // прочитаем его заданное количество раз двумя способами
    {
        LOG_DURATION("multiple get");
        ifstream test_in("test.txt");
        for (int i = 0; i < READ_COUNT; ++i) {
            test_in.seekg(0);
            ReadExact(test_in, buffer.data(), FILE_SIZE);
        }
    }

    {
        LOG_DURATION("stream read");
        ifstream test_in("test.txt");
        for (int i = 0; i < READ_COUNT; ++i) {
            test_in.seekg(0);
            test_in.read(buffer.data(), FILE_SIZE);
        }
    }
}