#pragma once

#include "people.h"

/*
    Надзиратель за уровнем удовлетворённости.
    Способен наблюдать за состоянием человека
    Если уровень удовлетворённости человека опустится ниже минимального уровня, Надзиратель
    побуждает человека танцевать до тех пор, пока уровень уровень удовлетворённости
    не станет больше или равен максимальному значению
*/
class SatisfactionSupervisor : public PersonObserver {
public:
    // Конструктор принимает значение нижнего и верхнего уровня удовлетворённости
    SatisfactionSupervisor(int min_satisfaction, int max_satisfaction) : min_satisfaction_(min_satisfaction), max_satisfaction_(max_satisfaction) {
    }

    void OnSatisfactionChanged(Person &person, int old_value, int new_value) override {
        // если старое значение больше нового, значит удовлетворенность потерялась вследствие работы или учебы, и если она стала меньше
        // min_satisfaction_, то нужно танцевать
        // если же старое значение меньше нового, значит идет процесс повышения удовлетворенности до тех пор пока она не станет
        // больше или равно max_satisfaction_
        if (old_value > new_value && new_value < min_satisfaction_) {
            while (max_satisfaction_ > person.GetSatisfaction()) {
                person.Dance();
            }
        }
    }

private:
    int min_satisfaction_;
    int max_satisfaction_;
};