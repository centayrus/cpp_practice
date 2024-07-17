#include "transport_catalogue.h"

#include <algorithm>
#include <iomanip>

// Добавление остановки в базу
void TransportCatalogue::AddStop(const std::string &stop_name, const Coordinates &coordinate) {
    stops_list_.push_back({stop_name, coordinate});
    auto stop_ptr = &stops_list_.back();
    stopname_to_stop_[stops_list_.back().stop_name] = stop_ptr;
}

// Добавление маршрута в базу
void TransportCatalogue::AddBus(const std::string &bus_name, const std::vector<std::string_view> &route) {
    std::vector<const Stop *> stop_list_for_bus;
    for (const auto &stop : route) {
        if (stopname_to_stop_.count(stop)) {
            Stop *stop_ptr = stopname_to_stop_.at(stop);
            stop_list_for_bus.push_back(stop_ptr);
        }
    }
    // маршрут и список остановок
    bus_routes_.push_back({bus_name, stop_list_for_bus});
    // ссылка на имя маршрута и дек маршрута-остновок
    busname_to_bus_.insert({bus_routes_.back().bus_route, &bus_routes_.back()});
    // Заполнение мапы для статистики остановок
    BusToStopFill(&bus_routes_.back(), bus_routes_.back().stops);
}

// Реализация приватного метода для заполнения статистики остановки
void TransportCatalogue::BusToStopFill(const Bus *bus_route, std::vector<const Stop *> stop_list) {
    if (bus_route) {
        for (const auto &stops : stop_list) {
            stopname_to_bus_[stops->stop_name].insert(bus_route);
        }
    }
}

// Поиск маршрута
BusStat TransportCatalogue::ReportBusStatistic(std::string_view request) const {
    auto bus_pos = busname_to_bus_.find(request);
    if (bus_pos == busname_to_bus_.end()) {
        return {};
    }
    Bus bus = *(*bus_pos).second;
    int common_stops_count = static_cast<int>(bus.stops.size());
    bool first_cycle = true;
    double total_distance = 0.;
    Coordinates prev_location;
    std::unordered_set<std::string_view> uniq_stops;
    for (const auto *stop_item : bus.stops) {
        uniq_stops.insert(stop_item->stop_name);
    }
    int uniq_stops_count = static_cast<int>(uniq_stops.size());
    // Рассчет дистанции маршрута
    for (const auto stop : bus.stops) {
        if (!first_cycle) {
            total_distance += ComputeDistance(prev_location, stop->coordinate);
        }
        first_cycle = false;
        prev_location = stop->coordinate;
    } //
    return {common_stops_count, uniq_stops_count, total_distance};
}

StopStat TransportCatalogue::ReportStopStatistic(std::string_view stopname) const {
    // Контейнер unordered_set чтобы избежать дубли маршрутов
    std::unordered_set<const Bus *> stop_stat;
    std::string_view stop;
    if (stopname_to_stop_.count(stopname)) {
        stop = stopname;
    }
    auto stop_stat_pos = stopname_to_bus_.find(stopname);
    std::vector<const Bus *> v_stop_stat;
    if (stop_stat_pos != stopname_to_bus_.end()) {
        v_stop_stat.reserve((*stop_stat_pos).second.size());
        v_stop_stat = {(*stop_stat_pos).second.begin(), (*stop_stat_pos).second.end()};
    }
    // Сортировка вектора для корректного вывода статистики
    std::sort(v_stop_stat.begin(), v_stop_stat.end(), [](const Bus *lhs, const Bus *rhs) {
        return std::lexicographical_compare((*lhs).bus_route.begin(), (*lhs).bus_route.end(),
                                            (*rhs).bus_route.begin(), (*rhs).bus_route.end());
    });
    return {stop, v_stop_stat};
}

void TransportCatalogue::SetDistance(const std::string &stop_name, const std::unordered_map<std::string, double> &dist) {
    auto a_stop_ptr = *stopname_to_stop_.find(stop_name)->second;
    for (const auto &stop_distance : dist) {
        auto b_stop_ptr = *stopname_to_stop_.find(stop_distance.first)->second;
        a_stop_ptr.distance[{&a_stop_ptr, &b_stop_ptr}] = stop_distance.second;
    }
}

// double TransportCatalogue::GetDistance() const {
// }
