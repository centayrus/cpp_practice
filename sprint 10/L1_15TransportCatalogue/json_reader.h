#pragma once
#include <string>
#include <variant>

#include "json.h"
#include "request_handler.h"
#include "transport_catalogue.h"
#include "map_renderer.h"

// Парсинг и загрузка базы справочника

json::Node BusStatLoad(const BusStat bus_stat, const int req_id);

json::Node StopStatLoad(const StopStat stop_stat, const int req_id);
// Загрузка данных в справочник
void LoadCatalogue(TransportCatalogue &db, const std::vector<json::Node> &base_req);

json::Document GetReqsResults(const RequestHandler &req_handler, const std::vector<json::Node> &base_req);

void FillRenderSets(json::Node render_node);
