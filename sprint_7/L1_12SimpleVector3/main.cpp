#include "simple_vector.h"

#include <cassert>
#include <stdexcept>

//using namespace std;

void TestReserveConstructor() {
    using namespace std::literals;
    std::cout << "TestReserveConstructor"s << std::endl;
    SimpleVector<int> v(Reserve(5));
    assert(v.GetCapacity() == 5);
    assert(v.IsEmpty());
    std::cout << "Done!"s << std::endl;
}

void TestReserveMethod() {
    using namespace std::literals;
    std::cout << "TestReserveMethod"s << std::endl;
    SimpleVector<int> v;
    // зарезервируем 5 мест в векторе
    v.Reserve(5);
    assert(v.GetCapacity() == 5);
    assert(v.IsEmpty());

    // попытаемся уменьшить capacity до 1
    v.Reserve(1);
    // capacity должно остаться прежним
    assert(v.GetCapacity() == 5);
    // поместим 10 элементов в вектор
    for (int i = 0; i < 10; ++i) {
        v.PushBack(i);
    }
    assert(v.GetSize() == 10);
    // увеличим capacity до 100
    v.Reserve(100);
    // проверим, что размер не поменялся
    assert(v.GetSize() == 10);
    assert(v.GetCapacity() == 100);
    // проверим, что элементы на месте
    for (int i = 0; i < 10; ++i) {
        assert(v[i] == i);
    }
    std::cout << "Done!"s << std::endl;
}

int main() {
       TestReserveConstructor();
       TestReserveMethod();
       return 0;
}
