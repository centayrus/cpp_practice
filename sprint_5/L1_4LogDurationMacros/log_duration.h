#pragma once

#include <chrono>
#include <iostream>
#include <string>

// можно сгенерить уникальное название переменной через конкатенацию константного литерала и номера строки
// #define PROFILE_CONCAT_INTERNAL(X, Y) X ## Y
// #define PROFILE_CONCAT(X, Y) PROFILE_CONCAT_INTERNAL(X, Y)
// #define UNIQUE_VAR_NAME_PROFILE PROFILE_CONCAT(profileGuard, __LINE__)  
// но в данном случае присваиваю имя guard, поскольку они разнесены по разным областям видимости
#define LOG_DURATION(x) LogDuration guard(x) 

class LogDuration {
public:
    // заменим имя типа std::chrono::steady_clock
    // с помощью using для удобства
    using Clock = std::chrono::steady_clock;

    LogDuration(const std::string &oper_type)
    : operation_type_(oper_type)  {
    }

    ~LogDuration() {
        using namespace std::chrono;
        using namespace std::literals;

        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        std::cerr << operation_type_ << ": "s << duration_cast<milliseconds>(dur).count() << " ms"s << std::endl;
    }

private:
    const Clock::time_point start_time_ = Clock::now();
    std::string operation_type_;
};