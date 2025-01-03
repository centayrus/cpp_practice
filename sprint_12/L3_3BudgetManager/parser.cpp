#include "parser.h"
// разработайте менеджер личного бюджета самостоятельно
// Parser::Parser(Date f, Date t, double earn) : from_(f),
// to_(t), earnings_(earn) {}
void Parser::SetDateFrom(const Date from) { from_ = from; }
void Parser::SetDateTo(const Date to) { to_ = to; }
void Parser::SetEarnings(const double earnings) { earnings_ = earnings; }

const Date Parser::GetDateFrom() const { return *from_; }
const Date Parser::GetDateTo() const { return *to_; }
double Parser::GetEarnings() const { return earnings_; }

void ParserRead::ParseQuery(std::string_view query) {
    SetDateFrom(Date(std::string_view(query.substr(0, query.find_first_of(' ')))));
    SetDateTo(Date(std::string_view(query.substr(query.find_first_of(' ') + 1, 
    query.npos - query.find_first_of(' ') - 1))));
}

void ParserModify::ParseQuery(std::string_view query) {
    SetDateFrom(Date(std::string_view(query.substr(0, query.find_first_of(' ')))));
    SetDateTo(Date(std::string_view(query.substr(query.find_first_of(' ') + 1, 
    query.find_last_of(' ') - query.find_first_of(' ') - 1))));
    SetEarnings(std::stod(std::string(query.substr(query.find_last_of(' ') + 1, 
    query.npos))));
}