#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
public:
    explicit Domain(const string& domain) : domain_name_(domain) {}

    const string& GetDomainName() const {
        return domain_name_;
    }

    bool operator==(const Domain& other) const {
        return domain_name_ == other.domain_name_;
    }

    bool IsSubdomain(const Domain& check_domain) const {
        const string& check_name = check_domain.GetDomainName();

        if (domain_name_.size() < check_name.size()) {
            return false;
        }

        // Проверяем, совпадает ли конец строки
        size_t pos = domain_name_.size() - check_name.size();
        if (domain_name_.compare(pos, string::npos, check_name) == 0) {
            // Убедимся, что перед check_name стоит точка или это начало строки
            return (pos == 0 || domain_name_[pos - 1] == '.');
        }
        return false;
    }

private:
    string domain_name_;
};

class DomainChecker {
public:
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end) {
        domains_.assign(begin, end);
        // Сортируем домены в обратном порядке (по частям справа налево)
        sort(domains_.begin(), domains_.end(), [](const Domain& lhs, const Domain& rhs) {
            return std::lexicographical_compare(
                rhs.GetDomainName().rbegin(), rhs.GetDomainName().rend(),
                lhs.GetDomainName().rbegin(), lhs.GetDomainName().rend());
        });
    }

    bool IsForbidden(const Domain& check_domain) const {
        for (const Domain& dom : domains_) {
            if (check_domain.IsSubdomain(dom) || check_domain == dom) {
                return true;
            }
        }
        return false;
    }

private:
    vector<Domain> domains_;
};

// Чтение доменов
vector<Domain> ReadDomains(istream& input, size_t count) {
    vector<Domain> domains;
    string line;
    while (count-- && getline(input, line)) {
        domains.emplace_back(line);
    }
    return domains;
}

template <typename Number>
Number ReadNumberOnLine(istream &input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

// Тестирование
void TestInputDomains() {
    string forbid_test_data = "gdz.ru\n"
                              "maps.me\n"
                              "m.gdz.ru\n"
                              "com";
    istringstream forbid_input_stream(forbid_test_data);
    vector<Domain> forbid_domains = ReadDomains(forbid_input_stream, 4);
    DomainChecker checker(forbid_domains.begin(), forbid_domains.end());

    string check_test_data = "gdz.ru\n"
                             "gdz.com\n"
                             "m.maps.me\n"
                             "alg.m.gdz.ru\n"
                             "maps.com\n"
                             "maps.ru\n"
                             "gdz.ua";
    istringstream check_input_stream(check_test_data);
    vector<Domain> test_domains = ReadDomains(check_input_stream, 7);

    assert(checker.IsForbidden(test_domains[0]) == true);  // gdz.ru
    assert(checker.IsForbidden(test_domains[1]) == true);  // gdz.com
    assert(checker.IsForbidden(test_domains[2]) == true);  // m.maps.me
    assert(checker.IsForbidden(test_domains[3]) == true);  // alg.m.gdz.ru
    assert(checker.IsForbidden(test_domains[4]) == true);  // maps.com
    assert(checker.IsForbidden(test_domains[5]) == false); // maps.ru
    assert(checker.IsForbidden(test_domains[6]) == false); // gdz.ua

    cout << "All tests passed!" << endl;
}

int main() {
    TestInputDomains();

    size_t forbidden_count = ReadNumberOnLine<size_t>(cin);
    vector<Domain> forbidden_domains = ReadDomains(cin, forbidden_count);
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    size_t check_count = ReadNumberOnLine<size_t>(cin);
    vector<Domain> test_domains = ReadDomains(cin, check_count);

    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}
