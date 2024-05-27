#pragma once
#include <deque>
#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "geo.h"

struct Stop {
    std::string stop_name;
    Coordinates coordinate;
};

struct Bus {
    std::string bus_route;
    std::vector<const Stop *> stops;
};

struct BusStat {
    explicit operator bool() const {
        if (stop_count) {
            return true;
        } else {
            return false;
        }
    }

    bool operator!() const {
        return !operator bool();
    }
    int stop_count;
    int uniq_stops;
    double total_distance;
};

struct StopStat {
    explicit operator bool() const {
        if (!stop_name.empty()) {
            return true;
        } else {
            return false;
        }
    }

    bool operator!() const {
        return !operator bool();
    }
    std::string_view stop_name;
    std::vector<const Bus *> bus_routes;
};

class TransportCatalogue {

public:
    void AddStop(const std::string &stop_name, const Coordinates &coordinate);

    void AddBus(const std::string &bus_name, const std::vector<std::string_view> route);

    BusStat FindBus(std::string_view request) const;

    StopStat GetStopStat(std::string_view stopname) const;

    size_t GetStopCount() const;

    size_t GetBusCount() const;

    size_t GetStopnameToStopSize() const;

    size_t GetBusnameToBusSize() const;

private:
    std::deque<Stop> stops_list_;
    std::unordered_map<std::string_view, Stop *> stopname_to_stop_;
    std::deque<Bus> bus_routes_;
    std::unordered_map<std::string_view, Bus *> busname_to_bus_;
    std::unordered_map<std::string_view, std::unordered_set<const Bus *>> stopname_to_bus_;

    void BusToStopFill(const Bus &bus_route, std::vector<const Stop *> stop_list);
};