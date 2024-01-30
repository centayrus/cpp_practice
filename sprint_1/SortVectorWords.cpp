#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <cctype>
using namespace std;

int main()
{
    // ѝчитайте входные данные и ѝформируйте вывод программы
    string words = "8 quantity AMOUNT Selection Search 4ever music Mickey market";
    string each_word;
    // getline(cin, words);
    vector<string> word_row;
    for (const char c : words)
    {
        if (c == ' ')
        {
            if (!each_word.empty())
            {
                word_row.push_back(each_word);
                each_word.clear();
            }
        }
        else
        {
            // if (each_word.size() > 15)
            // {
            //     cout << "Expression too long" << endl;
            //     ;
            //     return 0;
            // }
            each_word += c;
        }
    }
    if (!each_word.empty())
    {
        word_row.push_back(each_word);
    }

    // if (stoi(word_row[0]) < 0 || stoi(word_row[0]) > 1000)
    // {
    //     cout << "Argument is too match" << endl;
    //     return 0;
    // }
    vector<string> word_clean;
    for (int i = 1; i <= stoi(word_row[0]); i++)
    {
        word_clean.push_back(word_row[i]);
    }

    sort(word_clean.begin(), word_clean.end(), [](const string &l, const string &r) -> bool
         { return lexicographical_compare(
               l.begin(), l.end(),
               r.begin(), r.end(),
               [](const char &c1, const char &c2) -> bool
               { return tolower(c1) < tolower(c2); }); });

    for (string str : word_clean)
    {
        cout << str << " "s;
    }
    cout << endl;
}

//,
//                [](char c1, char c2) -> char
//                { return tolower(c1, locale{}), tolower(c2, locale{}); }

/*
8 quantity AMOUNT Selection Search 4ever music Mickey market
 */