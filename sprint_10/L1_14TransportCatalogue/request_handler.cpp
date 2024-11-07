#include "request_handler.h"

RequestHandler::RequestHandler(const TransportCatalogue &db) : db_(db) {}

BusStat RequestHandler::GetBusStat(const std::string_view &bus_name) const {
    return db_.ReportBusStatistic(bus_name);
}

StopStat RequestHandler::GetBusesByStop(const std::string_view &stop_name) const {
   return db_.ReportStopStatistic(stop_name);
}
