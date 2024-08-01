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
//using stop_pair = std::unordered_map<std::pair<Stop*, Stop*>, double, StopDistanceHasher>;

struct Stop;

class StopDistanceHasher {
public:
    size_t operator()(const std::pair<const Stop *, const Stop *> &interval) const {
        std::hash<const void *> hasher;
        std::size_t h1 = hasher(interval.first);
        std::size_t h2 = hasher(interval.second);
        return combineHashes(std::move(h1), std::move(h2));
    }

private:
    // Комбинируем два хеша в один
    std::size_t combineHashes(const std::size_t h1, const std::size_t h2) const {
        return h1 ^ (h2 << 1);
    }
};

struct Stop {
    std::string stop_name;
    Coordinates coordinate;
    std::unordered_map<std::pair<const Stop*,const Stop*>, double, StopDistanceHasher> distance;
};

struct Bus {
    std::string bus_route;
    std::vector<const Stop *> stops;
};

struct BusStat {
    explicit operator bool() const {
        return (stop_count) ? true : false;
    }

    bool operator!() const {
        return !operator bool();
    }
    int stop_count;
    int uniq_stops;
    double total_distance;
    double dist_proportion;
};

struct StopStat {
    explicit operator bool() const {
        return (!stop_name.empty());
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

    void AddBus(const std::string &bus_name, const std::vector<std::string_view> &route);

    BusStat ReportBusStatistic(std::string_view request) const;

    StopStat ReportStopStatistic(std::string_view stopname) const;

    void SetDistance(const std::string_view stop_name, const std::vector<std::pair<std::string, double>> &dist);



private:
    std::deque<Stop> stops_list_;
    std::unordered_map<std::string_view, Stop *> stopname_to_stop_;
    std::deque<Bus> bus_routes_;
    std::unordered_map<std::string_view, Bus *> busname_to_bus_;
    std::unordered_map<std::string_view, std::unordered_set<const Bus *>> stopname_to_bus_;

    void BusToStopFill(const Bus *bus_route, std::vector<const Stop *> stop_list);
    double GetDistance(const Stop *prev_stop, const Stop *cur_stop) const;
};

