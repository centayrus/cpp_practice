#include <algorithm>
#include <sstream>
#include <vector>

#include "json_reader.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */

JsonReader::JsonReader();
JsonReader::JsonReader(json::Document doc) : json_document_(doc) {}

json::Document JsonReader::LoadJson(const std::string &s) {
    std::istringstream strm(s);
    json_document_ = json::Load(strm);
    return json_document_;
}

void JsonReader::LoadCatalogue(TransportCatalogue &db) {
    json::Node node = json_document_.GetRoot();
    auto base_req = node.AsMap().find("base_requests");
    if (base_req == node.AsMap().end()) {
        throw std::invalid_argument("base_requests is not exist");
    }
    auto array = (*base_req).second.AsArray();
    std::sort(*array.begin(), *array.end(), [](json::Node &lhs, json::Node &rhs) {
        json::Node type1 = lhs.AsMap().at("type");
        json::Node type2 = rhs.AsMap().at("type");
        return type1.AsString() > type2.AsString();
    });
    for (const auto &item : array) {
        if (item.AsMap().at("type").AsString() == "Stop") {
            db.AddStop(item.AsMap().at("name").AsString(), {item.AsMap().at("latitude").AsDouble(), item.AsMap().at("longitude").AsDouble()});
        } else {
            std::vector<std::string_view> string_vec;
            for (const auto &node1 : item.AsMap().at("stops").AsArray()) {
                string_vec.emplace_back(node1.AsString());
            }
            db.AddBus(item.AsMap().at("name").AsString(), string_vec);
        }
    }
    for (const auto &stop : array) {
        if (stop.AsMap().at("type") == "Stop") {
            for (const auto &stop_list : stop.AsMap().at("road_distances").AsMap()) {
                db.SetDistance(stop.AsMap().at("name").AsString(), stop_list.first, stop_list.second.AsInt());
            }
        }
    }
}

json::Document JsonReader::GetReqsResults(const RequestHandler &req_handler) const {
    json::Node node = json_document_.GetRoot();
    auto base_req = node.AsMap().find("stat_requests");
    std::string array = "[]";
    std::istringstream strm(array);
    json::Document result_doc = json::Load(strm);
    json::Node tmp_node;
    if (base_req == node.AsMap().end()) {
        throw std::invalid_argument("Statistic requests is absence");
    }
    for (auto &req : base_req->second.AsArray()) {
        auto req_id = req.AsMap().at("id").AsInt();
        if (req.AsMap().at("type") == "Stop") {
            std::optional<BusStat> bus_stat = req_handler.GetBusStat(req.AsMap().at("name").AsString());
            tmp_node = BusStatLoad(std::move(bus_stat), req_id);
        } else {
            std::optional<StopStat> stop_stat = req_handler.GetBusesByStop(req.AsMap().at("name").AsString());
            tmp_node = StopStatLoad(std::move(stop_stat), req_id);
        }

        const_cast<std::vector<json::Node>&>(result_doc.GetRoot().AsArray()).push_back(tmp_node);
    }
    return result_doc;
}

void JsonReader::PrintStatistics(const json::Document &doc, std::ostream &ostrm) const {
    json::Print(doc, ostrm);
}

json::Node JsonReader::BusStatLoad(/* json::Document& result_doc, */ const std::optional<BusStat> bus_stat, const int req_id) const {
    std::string json_str;
    if (!bus_stat.has_value()) {
        json_str += "{\"request_id\":";
        json_str += std::to_string(req_id);
        json_str += ",\"error_message\": \"not found'\"}";
    } else {
        json_str += "{\"curvature\":";
        json_str += std::to_string(bus_stat.value().dist_proportion);
        json_str += ",\"request_id\":";
        json_str += std::to_string(req_id);
        json_str += ",\"route_length\":";
        json_str += std::to_string(bus_stat.value().total_distance);
        json_str += ",\"stop_count\":";
        json_str += std::to_string(bus_stat.value().stop_count);
        json_str += ",\"unique_stop_count\":";
        json_str += std::to_string(bus_stat.value().uniq_stops);
        json_str += "}";
    }
    std::istringstream strm(json_str);
    json::Document doc_item = json::Load(strm);
    return doc_item.GetRoot();
}

json::Node JsonReader::StopStatLoad(/* json::Document& result_doc, */ const std::optional<StopStat> stop_stat, const int req_id) const {
    std::string json_str;
    if (!stop_stat.has_value()) {
        json_str += "{\"request_id\":";
        json_str += std::to_string(req_id);
        json_str += ",\"error_message\": \"not found'\"}";
    } else {
        json_str += "{\"buses\": [";
        bool is_first = true;
        for (const auto *bus : stop_stat.value().bus_routes) {
            if (!is_first) {
                json_str += ",";
            }
            json_str += bus->bus_route;
            is_first = false;
        }
        json_str += "],\"request_id\":";
        json_str += std::to_string(req_id);
        json_str += "}";
    }
    std::istringstream strm(json_str);
    json::Document doc_item = json::Load(strm);
    return doc_item.GetRoot();
}

std::ostream &EntryFunction(const std::string &requests, const TransportCatalogue &catalogue, std::ostream out) {
    JsonReader reader;
    RequestHandler req_handler(catalogue);
    auto doc = reader.LoadJson(requests);

    reader.LoadCatalogue(catalogue);

    auto doc2 = reader.GetReqsResults(req_handler, out);
    PrintStatistics(doc2, out);
    return out;
}
