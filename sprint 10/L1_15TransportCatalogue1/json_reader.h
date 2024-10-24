#pragma once
#include <string>
#include <variant>

#include "json.h"
#include "request_handler.h"
#include "transport_catalogue.h"
#include "map_renderer.h"

// Парсинг и загрузка базы справочника

json::Node BusStatLoad(const domain::BusStat bus_stat, const int req_id);

json::Node StopStatLoad(const domain::StopStat stop_stat, const int req_id);

// Загрузка данных в справочник
void LoadCatalogue(TransportCatalogue &db, const std::vector<json::Node> &base_req);

json::Document GetReqsResults(const RequestHandler &req_handler, const std::vector<json::Node> &base_req);

// заполнение атрибутами отрисовки
void FillRenderSets(const json::Node &render_node, RenderSets &render_sets);

// создание объектов ломаных
std::vector<svg::Polyline> MakePolylineRender(const RequestHandler &req_handler, const MapRenderer &renderer);

void RenderSchema(std::vector<svg::Polyline> &p, std::ostream &out, const MapRenderer &renderer);
  