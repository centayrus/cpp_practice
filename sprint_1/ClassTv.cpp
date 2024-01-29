#include <iostream>

using namespace std;

/* Допишите класс в соответствии с требованиями задания*/
class TV {
    bool is_turned_on_ = false;
    int current_channel_ = 1;

public:
    // Включает телевизор.
    void TurnOn() {
        // Напишите код этого метода
        is_turned_on_ = true;

    }

    // Выключает телевизор
    void TurnOff() {
        // Напишите код этого метода
        is_turned_on_ = false;
    }

    // Возвращает true, если телевизор включен и false, если телевизор выключен
    bool IsTurnedOn() {
        // Напишите код этого метода
        if (is_turned_on_) {
            return true;
        }
        return false;
    }

    // Возвращает номер текущего канала, либо 0, если телевизор был выключен.
    // Телевизор при выключении «запоминает» номер текущего канала,
    // а при включении — «восстанавливает» его.
    // При первом включении телевизор показывает канал №1.
    int GetCurrentChannel() {
        // Напишите код этого метода
        if (IsTurnedOn()) {
            return current_channel_;
        }
        return 0;
    }

    // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала, либо телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool SelectChannel(int channel) {
        // Напишите код этого метода
        if (IsTurnedOn() && channel >= 1 && channel <= 99) {
            current_channel_ = channel;
            return true;
        }
        return false;
    }

};

int main() {
    TV tv;
    cout << tv.IsTurnedOn() << ", channel:"s << tv.GetCurrentChannel() << endl;
    tv.TurnOn();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.SelectChannel(25);
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.TurnOff();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
}