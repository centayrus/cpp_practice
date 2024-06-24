#include <iostream>

using namespace std;

// Указатель на функцию без параметров, которая возвращает void
using Alarm = void (*)();

namespace {
// Поведение сигнализации определяется значением указателя alarm
Alarm alarm = nullptr;
}  // namespace

// Выпустить велоцираптора
void HostileAlarm() {
    cout << "Attack with velociraptor"sv << endl;
}

// Настраиваем сигнализацию на выпуск велоцираптора
void SetHostileAlarm() {
    cout << "Hostile alarm set" << endl;
    alarm = HostileAlarm;
}

void Test() {
    // Вызываем функцию, на которую ссылается указатель alarm
    alarm();
    cout << "Test succeeded"sv << endl;
}

int main() {
    Test();
} 