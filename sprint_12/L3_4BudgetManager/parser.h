#pragma once
#include "date.h"
#include <optional>

// напишите в этом классе код, ответственный за чтение запросов
class Parser {
public:
    virtual void ParseQuery(std::string_view query) = 0;
    void SetDateFrom(const Date from);
    void SetDateTo(const Date to);
    void SetEarnings(const double earnings);
    void SetTax(const double tax);
    void SetSpend(const double spend);

    const Date GetDateFrom() const;
    const Date GetDateTo() const;
    double GetEarnings() const;
    double GetTax() const;
    double GetSpend() const;

private:
    std::optional<Date> from_;
    std::optional<Date> to_;
    double earnings_ = 0.0;
    double tax_ = 0.0;
    double spend_ = 0.0;
};

class ParserRead : public Parser {
public:
    explicit ParserRead(std::string_view query) {
        ParseQuery(query);
    }
    void ParseQuery(std::string_view query) override;
};

class ParserModify : public Parser {
public:
    explicit ParserModify(std::string_view query) {
        ParseQuery(query);
    }
    void ParseQuery(std::string_view query) override;
};