#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char** argv) {
    // 1
    {
        fstream fout("telefon.txt", ios::out);
        fout << "У меня зазвонил телефон."s << endl;
        fout << "- Кто говорит?"s << endl;
    }

    // 2
  /*   {
        fstream fout("telefon.txt", ios::out | ios::app);
        fout << "- Слон."s << endl;
    } */
/*     {
        fstream fout("telefon.txt", ios::in | ios::out);
        fout.seekp(72);
        fout << "- Слон."s << endl;
        cout << "Writing at pos: "s << fout.tellp() << endl;
    } */
    {
        fstream fout("telefon.txt", ios::in | ios::out);
        fout.seekp(0, ios::end);
        fout << "на линии?"s << endl << "- Слон."s << endl;
        cout << "Writing at pos: "s << fout.tellp() << endl;
    }

    // 3
    {
        fstream fin("telefon.txt", ios::in);
        string str;
        while (getline(fin, str)) {
            cout << str << endl;
        }
    }
}