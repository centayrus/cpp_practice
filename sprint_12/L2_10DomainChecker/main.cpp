#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
    // разработайте класс домена
public:
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    Domain(std::string &domain) : domain_name_(domain) {
        reverse(domain_name_.begin(), domain_name_.end());
        domain_name_.push_back('.');
    }

    const std::string GetDomainName() const {
        return domain_name_;
    }

    // разработайте operator==
    bool operator==(const Domain &other) const {
        return domain_name_ == other.domain_name_;
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain &check_domain) const {
        const string &check_name = check_domain.GetDomainName();
        if (domain_name_.size() < check_name.size()) {
            return false;
        }
        // Проверяем, совпадает ли конец строки
        auto res = std::mismatch(check_domain.domain_name_.begin(), check_domain.domain_name_.end(), domain_name_.begin());
        return res.first == check_domain.domain_name_.end();
    }

private:
    std::string domain_name_;
};

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end) : domains_(begin, end) {

        // Сортируем домены в обратном порядке (по частям справа налево)
        sort(domains_.begin(), domains_.end(), [](const Domain &lhs, const Domain &rhs) {
            return lhs.GetDomainName() < rhs.GetDomainName();
        });
        auto pos_end = std::unique(domains_.begin(), domains_.end(), [](const Domain &lhs, const Domain &rhs) {
            return rhs.IsSubdomain(lhs);
        });
        domains_.erase(pos_end, domains_.end());
    }

    bool IsForbidden(const Domain &check_domain) const {
        auto iter = upper_bound(domains_.begin(), domains_.end(), check_domain, [](const Domain &lhs, const Domain &rhs) {
            return lhs.GetDomainName() < rhs.GetDomainName();
        });
        if (iter == domains_.begin())
            return false;
        else
            return check_domain.IsSubdomain(*prev(iter));
    }

private:
    // здесь 4 запрещенных домена
    std::vector<Domain> domains_;
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
std::vector<Domain> ReadDomains(std::istream &input, size_t count) {
    string line;
    std::vector<Domain> domains;
    size_t i = 0;
    while (i < count) {
        getline(input, line);
        Domain domain(line);
        domains.push_back(domain);
        ++i;
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

void TestInputDomains() {
    std::string forbid_test_data = "gdz.ru\n"
                                   "maps.me\n"
                                   "m.gdz.ru\n"
                                   "com";
    std::istringstream forbid_input_stream(forbid_test_data);
    const std::vector<Domain> forbid_domains = ReadDomains(forbid_input_stream, 4);
    assert(forbid_domains[0].GetDomainName() == "ur.zdg.");
    assert(forbid_domains[1].GetDomainName() == "em.spam.");
    assert(forbid_domains[2].GetDomainName() == "ur.zdg.m.");
    assert(forbid_domains[3].GetDomainName() == "moc.");
    DomainChecker checker(forbid_domains.begin(), forbid_domains.end());

    std::string check_test_data = "gdz.ru\n"
                                  "gdz.com\n"
                                  "m.maps.me\n"
                                  "alg.m.gdz.ru\n"
                                  "maps.com\n"
                                  "maps.ru\n"
                                  "gdz.ua";
    std::istringstream cjeck_input_stream(check_test_data);
    const std::vector<Domain> test_domains = ReadDomains(cjeck_input_stream, 7);

    assert(forbid_domains.size() == 4);
    assert(checker.IsForbidden(test_domains[0]) == true);
    assert(checker.IsForbidden(test_domains[1]) == true);
    assert(checker.IsForbidden(test_domains[2]) == true);
    assert(checker.IsForbidden(test_domains[3]) == true);
    assert(checker.IsForbidden(test_domains[4]) == true);
    assert(checker.IsForbidden(test_domains[5]) == false);
    assert(checker.IsForbidden(test_domains[6]) == false);
}

int main() {
    TestInputDomains();
    // список запрещенных доменов
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));

    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());
    // список доменов, которые нужно проверить
    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));

    for (const Domain &domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}