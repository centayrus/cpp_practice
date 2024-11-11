#pragma once

#include "transport_catalogue.h"

class RequestHandler {
public:
    // MapRenderer понадобится в следующей части итогового проекта
    RequestHandler(const TransportCatalogue& db);

    // Возвращает информацию о маршруте (запрос Bus)
    domain::BusStat GetBusStat(const std::string_view& bus_name) const;

    // Возвращает маршруты, проходящие через остановки
    domain::StopStat GetBusesByStop(const std::string_view& stop_name) const;
    // возвращает все маршруты со связанными данными
    std::unordered_map<std::string_view, domain::Bus *> GetAllBusRoutes() const;

private:
    // RequestHandler использует агрегацию объектов "Транспортный Справочник" и "Визуализатор Карты"
    const TransportCatalogue& db_;
};

