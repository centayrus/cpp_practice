#include "input_reader.h"
#include "log_duration.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <iterator>
#include <regex>

// using distances = std::unordered_map<std::string, double>;
using distances = std::vector<std::pair<std::string, double>>;
using Clock = std::chrono::steady_clock;
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

distances ParseDistances(std::string str) {
    // Позиция первой запятой
    size_t first_comma_pos = str.find(',');
    if (first_comma_pos == str.npos) {
        return {};
    }
    // Позиция второй запятой - заканчивается зона координат
    size_t second_comma_pos = str.find(',', first_comma_pos + 1);
    if (second_comma_pos == str.npos) {
        return {};
    }
    std::string substring = std::string(str.substr(second_comma_pos + 1));
    std::string to_stop;
    double dist;
    distances dist_to_stop;
    std::string::size_type pos_item_start = substring.find_first_not_of(',');
    std::string::size_type pos_item_end = substring.find_first_of(',');
    if (pos_item_end == substring.npos) {
        pos_item_end = substring.find_last_not_of(' ') + 1;
    }
    while (pos_item_start != pos_item_end) {
        // берем первую комбинацию
        std::string item = substring.substr(pos_item_start, pos_item_end - pos_item_start);
        std::string::size_type pos_to = item.find("to");
        std::string::size_type pos_m = item.find("m");
        // определение дистанции
        dist = std::stod(std::string(item.substr(0, pos_m)));
        // определение остановки
        to_stop = Trim(item.substr(pos_to + 2));
        auto p = substring.find_first_not_of(',', item.size() + 1);
        if (p == substring.npos) {
            substring = "";
        } else {
            substring = substring.substr(p);
        }
        dist_to_stop.push_back({to_stop, dist});
        pos_item_start = substring.find_first_not_of(',');
        pos_item_end = substring.find_first_of(',');
        if (pos_item_end == substring.npos) {
            pos_item_end = substring.find_last_not_of(' ') + 1;
        }
        if (pos_item_start == substring.npos) {
            break;
        }
    }
    return dist_to_stop;
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
    {
        LOG_DURATION("ParseCoordinates");
        for (const CommandDescription &command : query_queue) {
            if (Trim(command.command) == "Stop") {
                Coordinates c = ParseCoordinates(std::move(command.description)); // убрать мув
                catalogue.AddStop(command.id, std::move(c));
            } else {
                catalogue.AddBus(command.id, ParseRoute(std::move(command.description)));
            }
        }
    }
    {
        LOG_DURATION("ParseDistances");
        for (const CommandDescription &command : query_queue) {
            //   distances distance;
              if (command.command == "Stop") {
            distances distance = ParseDistances(command.description);
            catalogue.SetDistance(command.id, distance);
              }
            //  }
            // }
            //{
            //  LOG_DURATION("SetDistance");
            // for (const CommandDescription &command : query_queue) {
            //    distances distance;
            //    if (command.command == "Stop") {
            //  distance = ParseDistances(command.description);
            // catalogue.SetDistance(command.id, {{"cdbsoind", 9500}});
            //    }
        }
    }
}