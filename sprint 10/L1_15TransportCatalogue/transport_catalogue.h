#pragma once
#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "geo.h"
#include "domain.h"

class TransportCatalogue {

public:
    void AddStop(const std::string &name, const geo::Coordinates &coordinate);

    void AddBus(const std::string &bus_name, const std::vector<std::string_view> &route);

    BusStat ReportBusStatistic(std::string_view request) const;

    StopStat ReportStopStatistic(std::string_view stopname) const;

    void SetDistance(const std::string_view a_name, const std::string_view b_name, const double &dist);

    std::deque<Bus> &GetAllRoutes() const;

private:
    std::deque<Stop> stops_list_;
    std::unordered_map<std::string_view, Stop *> stopname_to_stop_;
    std::deque<Bus> bus_routes_;
    std::unordered_map<std::string_view, Bus *> busname_to_bus_;
    std::unordered_map<std::string_view, std::unordered_set<const Bus *>> stopname_to_bus_;
    std::unordered_map<std::pair<const Stop *, const Stop *>, double, StopDistanceHasher> stop_to_stop_dist_;

    double GetDistance(const Stop *prev_stop, const Stop *cur_stop) const;
};
