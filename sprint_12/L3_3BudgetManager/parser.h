#pragma once
#include "date.h"

// напишите в этом классе код, ответственный за чтение запросов
class Parser {
public:
    virtual void ParseQuery(std::string_view query) = 0;
   // Parser(Date f, Date t, double earn);
    void SetDateFrom(const Date from);
    void SetDateTo(const Date to);
    void SetEarnings(const double earnings);

    const Date GetDateFrom() const;
    const Date GetDateTo() const;
    double GetEarnings() const;
    //virtual ~Parser() = default;

private:
        std::optional<Date> from_;
    std::optional<Date> to_;
    double earnings_ = 0.0;
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