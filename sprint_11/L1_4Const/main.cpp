#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "log_duration.h"

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin), last(end) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

private:
    Iterator first, last;
};

template <typename Collection>
auto Head(Collection &v, const size_t top) {
    return IteratorRange{v.begin(), std::next(v.begin(), min(top, v.size()))};
}

struct Person {
    string name;
    int age, income;
    bool is_male;
};

vector<Person> ReadPeople(istream &input) {
    int count;
    input >> count;
    const auto pers = invoke([&] {
        vector<Person> pers(count);
        char gender;
        for (int i = 0; i < count; ++i) {
            input >> pers[i].name >> pers[i].age >> pers[i].income >> gender;
            pers[i].is_male = gender == 'M';
        }
        return pers;
    });
    return pers;
}

int main() {
    vector<Person> people;

    people = ReadPeople(cin);
    vector<Person *> ages;

    for (Person &person : people) {
        ages.emplace_back(&person);
    }
    sort(ages.begin(), ages.end(),
         [](const Person *lhs, const Person *rhs) {
             return lhs->name < rhs->name;
         });

    std::unordered_map<int, int> age_cou;
    for (const auto &pers : ages) {
        age_cou[pers->age] += 1;
    }

    IteratorRange range{ages.begin(), ages.end()};
    std::unordered_map<char, std::string> pop_name;
    if (range.begin() == range.end()) {

    } else {
        string *most_popular_name = &(*range.begin())->name;
        int count_m = 0;
        int count_w = 0;
        for (auto i = range.begin(); i != range.end();) {
            auto same_name_end = find_if_not(i, range.end(),
                                             [i](const Person *p) {
                                                 return p->name == (*i)->name;
                                             });
            auto cur_name_count = distance(i, same_name_end);
            if ((*i)->is_male) {
                if (cur_name_count > count_m) {
                    count_m = cur_name_count;
                    most_popular_name = &(*i)->name;
                    pop_name['M'] = *most_popular_name;
                }
            } else {
                if (cur_name_count > count_w) {
                    count_w = cur_name_count;
                    most_popular_name = &(*i)->name;
                    pop_name['W'] = *most_popular_name;
                }
            }
            i = same_name_end;
        }
    }

    std::vector<int> income_sum(people.size());
    int prev_income = 0;
    sort(range.begin(), range.end(),
         [](const Person *lhs, const Person *rhs) {
             return lhs->income > rhs->income;
         });

    for (size_t i = 0; i < people.size();) {
        prev_income += (*(range.begin() + i))->income;
        income_sum[i] = prev_income;
        i++;
    }

    for (string command; cin >> command;) {
        if (command == "AGE"s) {
            int adult_age;
            int people_cou = 0;
            cin >> adult_age;
            for (auto pair : age_cou) {
                if (pair.first >= adult_age) {
                    people_cou += pair.second;
                }
            }
            cout << "There are "s << people_cou << " adult people for maturity age "s
                 << adult_age << '\n';
        } else if (command == "WEALTHY"s) {
            int count;
            cin >> count;
            if (income_sum.at(count - 1)) {
                cout << "Top-"s << count << " people have total income "s << income_sum.at(count - 1) << '\n';
            }
        } else if (command == "POPULAR_NAME"s) {

            char gender;
            cin >> gender;
            if (pop_name.count(gender)) {
                cout << "Most popular name among people of gender "s << gender << " is "s << pop_name[gender] << '\n';
            } else {
                cout << "No people of gender "s << gender << '\n';
            }
        }
    }
}
