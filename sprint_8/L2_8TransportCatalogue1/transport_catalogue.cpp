#include "transport_catalogue.h"

void TransportCatalogue::AddStop(const std::string &stop_name, const Coordinates &coordinate) {
    stops_list_.push_back({stop_name, coordinate});
    auto stop_ptr = &stops_list_.back();
    stopname_to_stop_[stop_name] = stop_ptr;
    //  std::cout << "AddStop: " << stop_name << std::endl;
}

void TransportCatalogue::AddBus(const std::string &bus_name, const std::vector<std::string_view> route) {
    std::vector<Stop *> stop_list_for_bus;
    for (const auto stop : route) {
        if (stopname_to_stop_.count(stop)) {
            Stop *stop_ptr = stopname_to_stop_.at(stop);
            stop_list_for_bus.push_back(stop_ptr);
        } else {
            continue;
        }
    }
    bus_routes_.push_back({bus_name, stop_list_for_bus});
    busname_to_bus_.insert({bus_routes_.back().bus_route, &bus_routes_.back()});
}

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
    for (const auto stop : bus.stops) {
        if (!first_cycle) {
            total_distance += ComputeDistance(prev_location, stop->coordinate);
        }
        first_cycle = false;
        prev_location = stop->coordinate;
    }
    return {common_stops_count, uniq_stops_count, total_distance};
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
