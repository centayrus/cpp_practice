#pragma once

#include <string>

class Person;

// Наблюдатель за состоянием человека.
class PersonObserver {
public:
    // Этот метод вызывается, когда меняется состояние удовлетворённости человека
    virtual void OnSatisfactionChanged(Person & /* person */, int /* old_value */, int /* new_value */) {
        // Реализация метода базового класса ничего не делает
    }

protected:
    // Класс PersonObserver не предназначен для удаления напрямую
    ~PersonObserver() = default;
};

/*
    Человек.
    При изменении уровня удовлетворённости уведомляет
    связанного с ним наблюдателя
*/
class Person {
public:
    Person(const std::string &name, int age) : name_(name), age_(age) {
        // Напишите реализацию самостоятельно
    }

    int GetSatisfaction() const {
        return satisfaction_;
    }

    const std::string &GetName() const {
        return name_;
    }

    // «Привязывает» наблюдателя к человеку. Привязанный наблюдатель
    // уведомляется об изменении уровня удовлетворённости человека
    // Новый наблюдатель заменяет собой ранее привязанного
    // Если передать nullptr в качестве наблюдателя, это эквивалентно отсутствию наблюдателя
    void SetObserver(PersonObserver *observer) {
        // Напишите реализацию самостоятельно
        observer_ = observer;
    }

    int GetAge() const {
        return age_;
    }

    // Увеличивает на 1 количество походов на танцы
    // Увеличивает удовлетворённость на 1
    virtual void Dance() {
        // Напишите тело метода самостоятельно
        auto prev_satisfaction = satisfaction_;
        ++prev_satisfaction;
        SetSatisfaction(prev_satisfaction);
        ++dance_counter_;
    }

    int GetDanceCount() const {
        // Заглушка. Напишите реализацию самостоятельно
        return dance_counter_;
    }

    // Прожить день. Реализация в базовом классе ничего не делает
    virtual void LiveADay() {
        // Подклассы могут переопределить этот метод
    }

    virtual ~Person() = default;

private:
    std::string name_;
    PersonObserver *observer_ = nullptr;
    int age_;
    int satisfaction_ = 100;

protected:
    int dance_counter_ = 0;
    void SetSatisfaction(int value) {
        if (satisfaction_ != value) {
            int old_satisfaction = satisfaction_;
            satisfaction_ = value;
            // Если у человека есть наблюдатель, сообщаем ему об изменении удовлетворённости
            if (observer_) {
                observer_->OnSatisfactionChanged(*this, old_satisfaction, satisfaction_);
            }
        }
    }

};

// Рабочий.
// День рабочего проходит за работой
class Worker : public Person {
public:
    Worker(const std::string &name, int age) : Person(name, age) {
        // Напишите недостающий код
    }

    // Рабочий старше 30 лет и младше 40 за танец получает 2 единицы удовлетворённости вместо 1
    void Dance() override {
        // Напишите тело метода самостоятельно
        int satisfaction_nums = 1;
        if (const int age = GetAge(); age > 30 && age < 40) {
            satisfaction_nums = 2;
        }
        auto cur_satisfaction = GetSatisfaction();
        cur_satisfaction += satisfaction_nums;
        SetSatisfaction(cur_satisfaction);
        ++dance_counter_;
    }

    // День рабочего проходит за работой
    void LiveADay() override {
        // Подклассы могут переопределить этот метод
        Work();
    }

    // Возвращает значение счётчика сделанной работы
    int GetWorkDone() const {
        // Заглушка. Напишите реализацию самостоятельно
        return work_counter_;
    }
    // Увеличивает счётчик сделанной работы на 1, уменьшает удовлетворённость на 5
    void Work() {
        // Напишите тело метода самостоятельно
        ++work_counter_;
        auto cur_satisfaction = GetSatisfaction();
        cur_satisfaction -= 5;
        SetSatisfaction(cur_satisfaction);

    }

private:
    int work_counter_ = 0;
};

// Студент.
// День студента проходит за учёбой
class Student : public Person {
public:
    Student(const std::string &name, int age) : Person(name, age) {
        // Напишите недостающий код
    }

    // День студента проходит за учёбой
    void LiveADay() override {
        // Подклассы могут переопределить этот метод
        Study();
    }

    // Возвращает уровень знаний
    int GetKnowledgeLevel() const {
        // Заглушка, напишите реализацию самостоятельно
        return knowledge_level_;
    }
    // Учёба увеличивает уровень знаний на 1, уменьшает уровень удовлетворённости на 3
    void Study() {
        // Напишите реализацию самостоятельно
        auto prev_satisfaction = GetSatisfaction();
        prev_satisfaction -= 3;
        SetSatisfaction(prev_satisfaction);
        ++knowledge_level_;
        
    }

private:
    int knowledge_level_ = 0;
};