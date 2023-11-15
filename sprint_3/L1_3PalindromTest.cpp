#include <iostream>
#include <string>

using namespace std;

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные буквы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, - это не палиндромы
bool IsPalindrome(const string& text) {
    string word;
    for (const char c : text) {
        if (c == ' ') {
            continue;
        } else {
            word += c;
        }
    }

    int text_size = static_cast<int>(word.size());
    if (text_size == 0) {
        return false;
    }
    for (int i = 0; i < text_size / 2;) {
        if (word[i] == word[text_size - 1 - i]) {
            ++i;
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    string text;
    getline(cin, text);

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    } else {
        cout << "not a palindrome"s << endl;
    }
}