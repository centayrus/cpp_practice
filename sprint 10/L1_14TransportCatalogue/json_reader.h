#pragma once

#include <json.h>
#include <request_handler.h>
#include <transport_catalogue.h>

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */

// Парсинг и загрузка базы справочника

class JsonReader {
public:
    JsonReader(Document doc) : json_document_(doc) {}

// Загрузка сырых данных в json-документ
    Document LoadJson(const std::string &s);

// Загрузка данных в справочник
    void LoadCatalogue(const TransportCatalogue& db) const;

    Document GetReqsResults(const RequestHandler &req_handler, std::ostream &output) const

private:
    Document json_document_;

void BusStatLoad(Document& result_doc, const BusStat bus_stat) const;

void StopStatLoad(Document& result_doc, const StopStat stop_stat) const;

};