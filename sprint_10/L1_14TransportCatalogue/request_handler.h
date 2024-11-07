#pragma once

#include "transport_catalogue.h"

class RequestHandler {
public:
    // MapRenderer понадобится в следующей части итогового проекта
    RequestHandler(const TransportCatalogue& db);

    // Возвращает информацию о маршруте (запрос Bus)
    BusStat GetBusStat(const std::string_view& bus_name) const;

    // Возвращает маршруты, проходящие через
    StopStat GetBusesByStop(const std::string_view& stop_name) const;

private:
    // RequestHandler использует агрегацию объектов "Транспортный Справочник" и "Визуализатор Карты"
    const TransportCatalogue& db_;
};