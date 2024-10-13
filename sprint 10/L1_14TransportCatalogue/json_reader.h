#pragma once
#include <string>

#include "json.h"
#include "request_handler.h"
#include "transport_catalogue.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */

// Парсинг и загрузка базы справочника

class JsonReader {
public:
   explicit JsonReader();
   explicit JsonReader(json::Document doc);

// Загрузка сырых данных в json-документ
    json::Document LoadJson(const std::string &s);

// Загрузка данных в справочник
    void LoadCatalogue(TransportCatalogue& db);

    json::Document GetReqsResults(const RequestHandler &req_handler) const;

    void PrintStatistics(const json::Document &doc, std::ostream &ostrm) const;

private:
    json::Document json_document_;

json::Node BusStatLoad(/* json::Document& result_doc, */ const std::optional<BusStat> bus_stat, const int req_id) const;

json::Node StopStatLoad(/* json::Document& result_doc, */ const std::optional<StopStat> stop_stat, const int req_id) const;

};