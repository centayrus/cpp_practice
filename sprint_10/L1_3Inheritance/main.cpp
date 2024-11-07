#include "people.h"

#include <cassert>
#include <iostream>

int main() {
    using namespace std;

    try {
        Programmer programmer{"Bjarne Stroustrup"s, 69, Gender::MALE};
        programmer.AddProgrammingLanguage(ProgrammingLanguage::CPP);
        programmer.AddProgrammingLanguage(ProgrammingLanguage::JAVA);
        assert(programmer.CanProgram(ProgrammingLanguage::JAVA));
        //std::cout << programmer.GetName() << " " << programmer.GetAge() << '\n';
        //cout << programmer.GetGender() << '\n'

        Worker worker{"Mario"s, 42, Gender::MALE};
        worker.AddSpeciality(WorkerSpeciality::PLUMBER);
        assert(worker.HasSpeciality(WorkerSpeciality::PLUMBER));
        //std::cout << worker.GetName() << " " << worker.GetAge() << '\n';
        //cout << worker.GetGender() << '\n';
    } catch (...) {
        cout << "Exception was thrown"s << endl;
    }
    cout << "OK"s << endl;
}