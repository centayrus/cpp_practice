#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Gender { FEMALE, MALE };

struct Person {
    int age;           // возраст
    Gender gender;     // пол
    bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = range_copy.begin() + range_copy.size() / 2;
    nth_element(range_copy.begin(), middle, range_copy.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
    });
    return middle->age;
}

// напишите сигнатуру и реализацию функции PrintStats
void PrintStats(const vector<Person>& pers) {
    cout << "Median age = "s << ComputeMedianAge(pers.begin(), pers.end()) << endl;
    vector<Person> females;
        vector<Person> males;
        vector<Person> employed_females;
        vector<Person> unemployed_females;
        vector<Person> employed_males;
        vector<Person> unemployed_males;
    for (const auto p : pers) {
        
        if (p.gender == Gender::FEMALE) {
            females.push_back(p);
            if (p.is_employed) {
                employed_females.emplace_back(p);
            } else {
                unemployed_females.emplace_back(p);
            }
        } else if (p.gender == Gender::MALE) {
            males.push_back(p);
            if (p.is_employed) {
                employed_males.emplace_back(p);
            } else {
                unemployed_males.emplace_back(p);
            }
        }
    }
     cout << "Median age for females = "s << ComputeMedianAge(females.begin(), females.end()) << endl;
    cout << "Median age for males = "s << ComputeMedianAge(males.begin(), males.end()) << endl;
    cout << "Median age for employed females = "s << ComputeMedianAge(employed_females.begin(), employed_females.end()) << endl;
    cout << "Median age for unemployed females = "s << ComputeMedianAge(unemployed_females.begin(), unemployed_females.end()) << endl;
    cout << "Median age for employed males = " << ComputeMedianAge(employed_males.begin(), employed_males.end()) << endl;
     cout << "Median age for unemployed males = "s << ComputeMedianAge(unemployed_males.begin(), unemployed_males.end()) << endl;
}

int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},   {40, Gender::FEMALE, true},  {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},  {80, Gender::FEMALE, false}, {78, Gender::MALE, false},
        {10, Gender::FEMALE, false}, {55, Gender::MALE, true},
    };
    PrintStats(persons);
}