#include "transport_catalogue.h"

void TransportCatalogue::AddStop(const std::string& stop_name, const Coordinates &coordinate) {
    stops_list_.push_back({stop_name, coordinate});
    auto stop_ptr = &stops_list_.back();
    stopname_to_stop_.insert({stop_name, stop_ptr});
}

void TransportCatalogue::AddBus(const std::string& bus_name, const std::vector<std::string_view> route) {
    std::vector< Stop* > stop_list_for_bus;
    for (const auto stop : route) {
        if (stopname_to_stop_.count(stop)) {
            Stop *stop_ptr = stopname_to_stop_.at(stop);
            std::cout << stop << std::endl;
            stop_list_for_bus.push_back(stop_ptr);
        } else {
            continue;
        }
    }
    bus_routes_.push_back({bus_name, stop_list_for_bus});
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
    std::unordered_set<std::string_view> uniq_stops(bus.stops.begin(), bus.stops.end());
    int uniq_stops_count = static_cast<int>(uniq_stops.size());
    for (const auto stop : bus.stops) {
        if (!first_cycle) {
            total_distance += ComputeDistance(prev_location, stop->coordinate);
            first_cycle = false;
        }
        prev_location = stop->coordinate;
    }
    return {common_stops_count, uniq_stops_count, total_distance};
}

/* struct Bus {
    std::string bus_route;
    std::vector<Stop *> stops;
};

    std::deque<Stop> stops_list_;
    std::unordered_map<std::string_view, const Stop *> stopname_to_stop_;
std::deque<Bus> bus_routes_;
std::unordered_map<std::string_view, const Bus *> busname_to_bus_; */