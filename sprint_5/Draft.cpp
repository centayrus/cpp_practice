#include <filesystem>
#include <iostream>

using namespace std;

int main() {
    using filesystem::path;

    path p = path("a") / path("folder") / path("and") / path("..") / path("a") / path("file.txt");

    // выводим естественное представление пути в std::string
    cout << p.string() << endl;
    cout << __LINE__ << endl;
}