#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

template <typename Checker>
class PasswordCracker {
public:
    PasswordCracker(Checker check, string key)
        : check_(check)
        , curr_check_key_(move(key))
        , cached_passwords_()
    {
    }
    void SetCheck(Checker check, string key) {
        check_ = check;
        curr_check_key_ = move(key);
    }
    string BruteForce() const {
        // если готовый пароль есть в словаре, вернём его
        auto result = cached_passwords_.find(curr_check_key_);
        if (cached_passwords_.end() != result) {
            return result->second;
        }
        // если готового пароля нет, перейдём к подбору
        auto pass = BruteForceInternal(""s, 0);
        // не забудем добавить новый пароль в словарь готовых паролей
        cached_passwords_[move(curr_check_key_)] = pass;
        return pass;
    }
private:
    string BruteForceInternal(const string& begin, int n) const {
        if (n == 5) {
            return check_(begin) ? begin : ""s;
        }
        for (char c = 'A'; c != 'Z' + 1; ++c) {
            string res = BruteForceInternal(begin + string({c}), n + 1);
            if (!res.empty()) {
                return res;
            }
        }
        return {};
    }
    Checker check_;
    string curr_check_key_;
    //словарь для кеширования найденных паролей
    mutable unordered_map<string, string> cached_passwords_;
};

class PasswordChecker {
public:
    PasswordChecker(string match)
        : match_(match)
    {
    }
    bool operator()(const string& s) const {
        return s == match_;
    }
    void operator=(const PasswordChecker& other) {
        match_ = other.match_;
    }

private:
    string match_;
};

string GetShmandexPass(const PasswordCracker<PasswordChecker>& pass_cracker) {
    // если раскомментировать код ниже, программа не скомпилируется
    // PasswordChecker.check("BUY"s);
    // pass_cracker.SetCheck(check);
    return pass_cracker.BruteForce();
}

int main() {
    PasswordChecker check("HELLO"s);
    PasswordCracker password_cracker(check, ""s);
    cout << GetShmandexPass(password_cracker) << endl;
    cout << GetShmandexPass(password_cracker) << endl;
} 