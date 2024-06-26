#include "input_reader.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <regex>

using distances = std::unordered_map<std::string_view, int>;
/**
 * Парсит строку вида "10.123,  -30.1837" и возвращает пару координат (широта, долгота)
 */
Coordinates ParseCoordinates(std::string_view str) {
    static const double nan = std::nan("");

    auto not_space = str.find_first_not_of(' ');
    auto comma = str.find(',');

    if (comma == str.npos) {
        return {nan, nan};
    }

    auto not_space2 = str.find_first_not_of(' ', comma + 1);
    auto not_space3 = str.find_first_of(',', not_space2 + 1);

    double lat = std::stod(std::string(str.substr(not_space, comma - not_space)));
    double lng = std::stod(std::string(str.substr(not_space2, not_space3 - not_space2)));

    return {lat, lng};
}

distances ParseDistances(const std::string &str) {
    // std::regex regex("(\\d+m+[' ']{1,}+to)");
    // Позиция первой запятой
    size_t firstCommaPos = str.find(',');
    // Позиция второй запятой
    size_t secondCommaPos = str.find(',', firstCommaPos + 1);
    std::string substr = str.substr(secondCommaPos+1);
    // std::cout << substr << '\n';
    std::regex regex("(\\d+m\\s+to\\s+[^,]+)");
    std::sregex_iterator begin(substr.begin(), substr.end(), regex);
    std::sregex_iterator end;
    distances dist_map;
    while (begin != end) {
        std::smatch match = *begin;
        // std::cout << match.str() << '\n'; // Выводит найденные вхождения
        std::find_first_of(match.str(), 'm');
        ++begin;
        
    }
    return {};
}

/**
 * Удаляет пробелы в начале и конце строки
 */
std::string_view Trim(std::string_view string) {
    const auto start = string.find_first_not_of(' ');
    if (start == string.npos) {
        return {};
    }
    return string.substr(start, string.find_last_not_of(' ') + 1 - start);
}

/**
 * Разбивает строку string на n строк, с помощью указанного символа-разделителя delim
 */
std::vector<std::string_view> Split(std::string_view string, char delim) {
    std::vector<std::string_view> result;

    size_t pos = 0;
    while ((pos = string.find_first_not_of(' ', pos)) < string.length()) {
        auto delim_pos = string.find(delim, pos);
        if (delim_pos == string.npos) {
            delim_pos = string.size();
        }
        if (auto substr = Trim(string.substr(pos, delim_pos - pos)); !substr.empty()) {
            result.push_back(substr);
        }
        pos = delim_pos + 1;
    }

    return result;
}

/**
 * Парсит маршрут.
 * Для кольцевого маршрута (A>B>C>A) возвращает массив названий остановок [A,B,C,A]
 * Для некольцевого маршрута (A-B-C-D) возвращает массив названий остановок [A,B,C,D,C,B,A]
 */
std::vector<std::string_view> ParseRoute(std::string_view route) {
    if (route.find('>') != route.npos) {
        return Split(route, '>');
    }

    auto stops = Split(route, '-');
    std::vector<std::string_view> results(stops.begin(), stops.end());
    results.insert(results.end(), std::next(stops.rbegin()), stops.rend());

    return results;
}

CommandDescription ParseCommandDescription(std::string_view line) {
    auto colon_pos = line.find(':');
    if (colon_pos == line.npos) {
        return {};
    }

    auto space_pos = line.find(' ');
    if (space_pos >= colon_pos) {
        return {};
    }

    auto not_space = line.find_first_not_of(' ', space_pos);
    if (not_space >= colon_pos) {
        return {};
    }

    return {std::string(line.substr(0, space_pos)),
            std::string(line.substr(not_space, colon_pos - not_space)),
            std::string(line.substr(colon_pos + 1))};
}

void InputReader::ParseLine(std::string_view line) {
    auto command_description = ParseCommandDescription(line);
    if (command_description) {
        commands_.push_back(std::move(command_description));
    }
}

void InputReader::ApplyCommands([[maybe_unused]] TransportCatalogue &catalogue) const {
    std::vector<CommandDescription> query_queue;
    for (const auto &command : commands_) {
        query_queue.push_back(command);
    }
    // Сортировка запросов по типу
    std::sort(query_queue.begin(), query_queue.end(), [](CommandDescription lhs, CommandDescription rhs) {
        return lhs.command > rhs.command;
    });
    // Обработка запросов согласно очередности
    for (const CommandDescription &command : query_queue) {
        if (Trim(command.command) == "Stop") {
            distances dist = ParseDistances(command.description);
            Coordinates c = ParseCoordinates(std::move(command.description));
            catalogue.AddStop(command.id, std::move(c));
            // catalogue.SetDistance(command.id, );
        } else {
            catalogue.AddBus(command.id, ParseRoute(std::move(command.description)));
        }
    }
}
