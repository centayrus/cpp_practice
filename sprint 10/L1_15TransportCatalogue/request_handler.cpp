#include "request_handler.h"

RequestHandler::RequestHandler(const TransportCatalogue &db) : db_(db) {}

BusStat RequestHandler::GetBusStat(const std::string_view &bus_name) const {
    return db_.ReportBusStatistic(bus_name);
}

StopStat RequestHandler::GetBusesByStop(const std::string_view &stop_name) const {
   return db_.ReportStopStatistic(stop_name);
}

const std::unordered_map<std::string_view, Bus *> &RequestHandler::GetAllBusRoutes() const {
    auto bus_routes = db_.GetAllRoutes();
    std::vector<domain::Bus*> result;
    result.reserve(bus_routes_.)
    for (const auto& bus : bus_routes) {
        result.emplace_back(bus.second);
    }
    return result;
}

const std::deque<Stop> &RequestHandler::GetUniqueStops() const {
    return db_.GetUniqueStops();
}