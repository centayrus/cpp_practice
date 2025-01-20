#include "common.h"

#include <cctype>
#include <cmath>
#include <sstream>
#include <vector>

const int LETTERS = 26;
const int MAX_POSITION_LENGTH = 17;
const int MAX_POS_LETTER_COUNT = 3;

const Position Position::NONE = {-1, -1};

// Реализуйте методы:
bool Position::operator==(const Position rhs) const {
    return this->row == rhs.row && this->col == rhs.col;
}

bool Position::operator<(const Position rhs) const {
    return this->row < rhs.row && this->col < rhs.col;
}

bool Position::IsValid() const {
    return row < MAX_ROWS && col < MAX_COLS && row >= 0 && col >= 0;
}

std::string Position::ToString() const {
    if (row < 0 || row >= 16384 || col < 0 || col >= 16384) {
        return "";
    }
    std::string str;
    if (col < LETTERS) {
        str += ('A' + col); // просто порядковый номер от 0 до 25
    } else if (col >= LETTERS && col < LETTERS * LETTERS + LETTERS) {
        int divide = col / LETTERS; // определяем позицию первой буквы
        str = 'A' + (divide - 1);
        int diff = col - (LETTERS * divide); // определяем позицию второй буквы
        str += 'A' + diff;
    } else if (col >= LETTERS * LETTERS + LETTERS && col <= 16384) {
        int divide = col / (LETTERS * LETTERS); // Позиция первой буквы
        str = 'A' + (divide - 1);
        int diff = col - (LETTERS * LETTERS * divide);
        int diff_b = diff / LETTERS; // Позиция второй буквы
        str += 'A' + (diff_b - 1);
        int diff_c = col - (LETTERS * LETTERS * divide) - (diff_b * LETTERS);
        str += 'A' + diff_c; // Позиция третьей буквы
    }

    std::string row_str = std::to_string(row + 1);
    for (const auto chr : row_str) {
        str += chr;
    }
    return str;
}

Position Position::FromString(std::string_view str) {
    if (str.length() > MAX_POSITION_LENGTH) {
        return Position::NONE;
    }
    std::vector<int> letter_pos;
    std::string str1;
    int char_count = 0;
    int num_count = 0;
    for (const char &chr : str) {
        if (chr >= 'A' && chr <= 'Z') {
            ++char_count;
            if (num_count || char_count > MAX_POS_LETTER_COUNT) {
                return Position::NONE;
            }
            letter_pos.push_back(chr - 'A' + 1); // относительная позиция цифры в таблице ASCII
        } else if (chr >= '0' && chr <= '9') {
            if (!char_count) {
                return Position::NONE;
            }
            ++num_count;
            str1 += chr;
        } else {
            return Position::NONE;
        }
    }
    if (num_count == 0 || char_count == 0) {
        return Position::NONE; // Должны быть и буквы, и цифры
    }
    int row_num = std::stoi(str1) - 1;
    size_t let_size = letter_pos.size();
    int col_num;
    if (let_size == 1) {
        col_num = letter_pos[0] - 1;
    } else if (let_size == 2) {
        if (letter_pos[0] == 0) {
            ++letter_pos[0];
        }
        col_num = (letter_pos[0]) * LETTERS + (letter_pos[1]) - 1;
    } else {
        col_num = letter_pos[0] * LETTERS * LETTERS + letter_pos[1] * LETTERS +
                  letter_pos[2] - 1;
    }
    if (row_num < 0 || row_num >= 16384 || col_num < 0 || col_num >= 16384) {
        return Position::NONE;
    }
    return {row_num, col_num}; // Возвращаем новый объект Position
}