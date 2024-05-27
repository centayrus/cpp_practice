#include "transport_catalogue.h"

#include <algorithm>

// Добавление остановки в базу
void TransportCatalogue::AddStop(const std::string &stop_name, const Coordinates &coordinate) {
    stops_list_.push_back({stop_name, coordinate});
    auto stop_ptr = &stops_list_.back();
    stopname_to_stop_[stops_list_.back().stop_name] = stop_ptr;
}

// Добавление маршрута в базу
void TransportCatalogue::AddBus(const std::string &bus_name, const std::vector<std::string_view> route) {
    std::vector<const Stop *> stop_list_for_bus;

    for (const auto stop : route) {
        if (stopname_to_stop_.count(stop)) {
            Stop *stop_ptr = stopname_to_stop_.at(stop);
            stop_list_for_bus.push_back(stop_ptr);
        } else {
            continue;
        }
    }
    // маршрут и список остановок
    bus_routes_.push_back({bus_name, stop_list_for_bus});
    // ссылка на имя маршрута и дек маршрута-остновок
    busname_to_bus_.insert({bus_routes_.back().bus_route, &bus_routes_.back()});
    // Заполнение мапы для статистики остановок
    BusToStopFill(bus_routes_.back(), bus_routes_.back().stops);
}

// Реализация приватного метода для заполнения статистики остановки
void TransportCatalogue::BusToStopFill(const Bus &bus_route, std::vector<const Stop *> stop_list) {
    for (const auto stops : stop_list) {
        stopname_to_bus_[stops->stop_name].insert(&bus_route);
    }
}

// Поиск маршрута
BusStat TransportCatalogue::FindBus(std::string_view request) const {
    if (busname_to_bus_.count(request) == 0) {
        return {};
    }
    Bus bus = *busname_to_bus_.at(request);
    int common_stops_count = static_cast<int>(bus.stops.size());
    bool first_cycle = true;
    double total_distance = 0.;
    Coordinates prev_location;
    std::unordered_set<std::string_view> uniq_stops;
    for (const auto *l : bus.stops) {
        uniq_stops.insert(l->stop_name);
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

StopStat TransportCatalogue::GetStopStat(std::string_view stopname) const {
    // Контейнер unordered_set чтобы избежать дублей маршрутов
    std::unordered_set<const Bus *> stop_stat;
    std::string_view stop;
    if (stopname_to_stop_.count(stopname)) {
        stop = stopname;
    }
    if (stopname_to_bus_.count(stopname)) {
        stop_stat = stopname_to_bus_.at(stopname);
    }
    std::vector v_stop_stat(stop_stat.begin(), stop_stat.end());
    // Сортировка вектора для корректного вывода статистики
    std::sort(v_stop_stat.begin(), v_stop_stat.end(), [](const Bus *lhs, const Bus *rhs) {
        return std::lexicographical_compare((*lhs).bus_route.begin(), (*lhs).bus_route.end(),
                                            (*rhs).bus_route.begin(), (*rhs).bus_route.end());
    });
    return {stop, v_stop_stat};
}

size_t TransportCatalogue::GetStopCount() const {
    return stops_list_.size();
}

size_t TransportCatalogue::GetBusCount() const {
    return bus_routes_.size();
}

size_t TransportCatalogue::GetStopnameToStopSize() const {
    return stopname_to_stop_.size();
}

size_t TransportCatalogue::GetBusnameToBusSize() const {
    return busname_to_bus_.size();
}
