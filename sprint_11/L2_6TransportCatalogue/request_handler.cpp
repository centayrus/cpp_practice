#include "request_handler.h"

RequestHandler::RequestHandler(const TransportCatalogue &db) : db_(db) {}

domain::BusStat RequestHandler::GetBusStat(const std::string_view &bus_name) const {
    return db_.ReportBusStatistic(bus_name);
}

domain::StopStat RequestHandler::GetBusesByStop(const std::string_view &stop_name) const {
    return db_.ReportStopStatistic(stop_name);
}

std::unordered_map<std::string_view, domain::Bus *> RequestHandler::GetAllBusRoutes() const {
    return db_.GetAllRoutes();
}
