#include <iostream>
#include <map>
#include <string>

struct Vector3D {
    double x;
    double y;
    double z;
};

int main() {
    using namespace std;

    map<string, string>* string_to_string;

    cout << "char*: size:"s << sizeof(char*) << endl;
    cout << "int*: size:"s << sizeof(int*) << endl;
    cout << "double*: size:"s << sizeof(double*) << endl;
    cout << "Vector3D*: size:"s << sizeof(Vector3D*) << endl;
    cout << "map<string, string>*: size:"s << sizeof(string_to_string) << endl;
}

/* 
вывод программы на 64 битно
char*: size:8
int*: size:8
double*: size:8
Vector3D*: size:8
map<string, string>*: size:8

char*: size:4
int*: size:4
double*: size:4
Vector3D*: size:4
map<string, string>*: size:4
 */