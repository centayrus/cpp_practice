#pragma once
#include <deque>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "geo.h"

struct Stop {
    std::string stop_name;
    Coordinates coordinate;
    // double lat;
    // double lng;
};

struct Bus {
    std::string bus_route;
    std::vector<Stop *> stops;
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

class TransportCatalogue {

public:
    void AddStop(const std::string &stop_name, const Coordinates &coordinate);

    void AddBus(const std::string &bus_name, const std::vector<std::string_view> route);

    BusStat FindBus(std::string_view request) const;

    size_t GetStopCount() const;

    size_t GetBusCount() const;

    size_t GetStopnameToStopSize() const;

    size_t GetBusnameToBusSize() const;

private:
    std::deque<Stop> stops_list_;
    std::unordered_map<std::string_view, Stop *> stopname_to_stop_;
    std::deque<Bus> bus_routes_;
    std::unordered_map<std::string_view, Bus *> busname_to_bus_;
};