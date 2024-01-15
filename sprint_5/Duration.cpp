#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace chrono;

int main() {
    cout << "Ожидание 5s..."s << endl;
    const auto start_time = steady_clock::now();

    // операция - ожидание 5 секунд
    this_thread::sleep_for(seconds(5));
    const auto end_time = steady_clock::now();

    const auto dur = end_time - start_time;
    cerr << "Продолжительность сна: "s << duration_cast<milliseconds>(dur).count() << " ms"s << endl;

    cout << "Ожидание завершено"s << endl;
}