#include "parser.h"
// разработайте менеджер личного бюджета самостоятельно
// Parser::Parser(Date f, Date t, double earn) : from_(f),
// to_(t), earnings_(earn) {}
using namespace std::string_view_literals;

void Parser::SetDateFrom(const Date from) { from_ = from; }
void Parser::SetDateTo(const Date to) { to_ = to; }
void Parser::SetEarnings(const double earnings) { earnings_ = earnings; }
void Parser::SetTax(const double tax) { tax_ = tax; }
void Parser::SetSpend(const double spend) { spend_ = spend; }

const Date Parser::GetDateFrom() const { return *from_; }
const Date Parser::GetDateTo() const { return *to_; }
double Parser::GetEarnings() const { return earnings_; }
double Parser::GetTax() const { return tax_; }
double Parser::GetSpend() const { return spend_; }

void ParserRead::ParseQuery(std::string_view query) {
    std::string_view query_type = query.substr(0, query.find_first_of(' '));
    query.remove_prefix(query_type.size() + 1);

    SetDateFrom(Date(std::string_view(query.substr(0, query.find_first_of(' ')))));
    SetDateTo(Date(std::string_view(query.substr(query.find_first_of(' ') + 1,
                                                 query.npos - query.find_first_of(' ') - 1))));
}

void ParserModify::ParseQuery(std::string_view query) {
    std::string_view query_type = query.substr(0, query.find_first_of(' '));
    if (query_type == "Earn"sv) {
        SetEarnings(std::stod(std::string(query.substr(query.find_last_of(' ') + 1, query.npos))));
    }
    if (query_type == "PayTax"sv) {
        SetTax(std::stod(std::string(query.substr(query.find_last_of(' ') + 1, query.npos))));
    }
    if (query_type == "Spend"sv) {
        SetSpend(std::stod(std::string(query.substr(query.find_last_of(' ') + 1, query.npos))));
    }
    query.remove_prefix(query_type.size() + 1);

    SetDateFrom(Date(std::string_view(query.substr(0, query.find_first_of(' ')))));
    SetDateTo(Date(std::string_view(query.substr(query.find_first_of(' ') + 1,
                                                 query.find_last_of(' ') - query.find_first_of(' ') - 1))));
}