#include "people.h"

#include <stdexcept>

using namespace std;

Person::Person(const string& name, int age, Gender gender) : name_(name), age_(age), gender_(gender) {
}

const string& Person::GetName() const {
    // Заглушка, реализуйте метод самостоятельно;
    if (name_.empty()) {
    throw std::logic_error("Not implemented"s);
    }
    return name_;
}

int Person::GetAge() const {
    // Заглушка, реализуйте метод самостоятельно
    
    return age_;
}

Gender Person::GetGender() const {
    // Заглушка, реализуйте метод самостоятельно
    return gender_;
}

Programmer::Programmer(const string& name, int age, Gender gender) : Programmer::Person(name, age, gender) {
}

void Programmer::AddProgrammingLanguage(ProgrammingLanguage language) {
    // Заглушка, реализуйте метод самостоятельно
    language_.insert(language);
}

bool Programmer::CanProgram(ProgrammingLanguage language) const {
    // Заглушка, реализуйте метод самостоятельно
    auto value = language_.find(language);
    if (value == language_.end()) {
        return false;
    }
    return true;
}

Worker::Worker(const string& name, int age, Gender gender) : Programmer::Person(name, age, gender) {
    // Заглушка, реализуйте конструктор самостоятельно
}

void Worker::AddSpeciality(WorkerSpeciality speciality) {
    // Заглушка, реализуйте метод самостоятельно
    speciality_.insert(speciality);
}

bool Worker::HasSpeciality(WorkerSpeciality speciality) const {
    // Заглушка, реализуйте метод самостоятельно
    auto value = speciality_.find(speciality);
    if (value == speciality_.end()) {
        return false;
    }
    return true;
}