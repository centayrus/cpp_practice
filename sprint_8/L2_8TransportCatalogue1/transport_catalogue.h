#pragma once
#include <deque>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Stop {
    std::string stop_name;
    double lat;
    double lng;
};

class TransportCatalogue {

public:

void AddStop()


private:
    std::deque<Stop> stops_list_;
    std::unordered_map<std::string_view, Stop *> stopname_to_stop_;
    std::vector<Stop *> bus_route_;
    std::vector<std::string> query_queue_;
};