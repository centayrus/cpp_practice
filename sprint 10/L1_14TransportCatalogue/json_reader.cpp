#include "json_reader.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */

Document JsonReader::LoadJson(const std::string &s) {
    std::istringstream strm(s);
    json_document_ = json::Load(strm);
    return json_document_;
}

void JsonReader::LoadCatalogue(const TransportCatalogue &db) const {
    Node node = json_document_.GetRoot();
    auto base_req = node.AsMap().find("base_requests");
    if (base_req == node.AsMap().end()) {
        throw std::invalid_argument("base_requests is not exist")
    }
    auto array = (*base_req).second.AsArray();
    std::sort(array.begin(), array.end(), [](Node lhs, Node rhs) {
        return lhs.AsMap()["type"] > rhs.AsMap()["type"];
    });
    for (const auto &item : array) {
        if (item.AsMap()["type"] == "Stop") {
            db.AddStop(item.AsMap()["name"], {item.AsMap()["latitude"], item.AsMap()["longitude"]});
        } else {
            db.AddBus(item.AsMap()["name"], item.AsMap()["stops"]);
        }
    }
    for (const auto &stop : array) {
        if (stop.AsMap()["type"] == "Stop") {
            for (const auto &stop_list : stop.AsMap()["road_distances"]) {
                db.SetDistance(item.AsMap()["name"], stop_list.first, stop_list.second) {
                }
            }
        }
    }
}


Document JsonReader::GetReqsResults(const RequestHandler &req_handler, std::ostream &output) const {
    Node node = json_document_.GetRoot();
    auto base_req = node.AsMap().find("stat_requests");
    std::string array = "[]";
    std::istringstream strm(array);
    Document result_doc = json;
    if (base_req == node.AsMap().end()) {
        throw std::invalid_argument("stat_requests is absent")
    }
    for (const auto &req : (*base_req).second) {
        auto req_id = req.AsMap()["id"];
        if (req.AsMap()["type"] == "Stop") {
            auto bus_stat = req_handler.GetBusStat(req.AsMap()["name"]);
            BusStatLoad(result_doc, std::move(bus_stat), req_id);
        } else {
            auto stop_stat = req_handler.GetBusesByStop(req.AsMap()["name"]);
            StopStatLoad(result_doc, std::move(stop_stat), req_id);
        }
    }
}

//  void Print(const Document &doc, std::ostream &output);

void JsonReader::BusStatLoad(Document &result_doc, const BusStat bus_stat, const int req_id) const {
    std::string json_str;
    json_str += "{\"curvature\":";
    json_str += bus_stat.dist_proportion;
    json_str += ",\"request_id\":";
    json_str += req_id;
    json_str += ",\"route_length\":";
    json_str += bus_stat.total_distance;
    json_str += ",\"stop_count\":";
    json_str += bus_stat.stop_count;
    json_str += ",\"unique_stop_count\":";
    json_str += bus_stat.uniq_stops;
    json_str += "}";
    std::istringstream strm(json_str);
    Document doc_item = json::Load(strm);
    result_doc.Get_root().AsArray().push_back(doc_item);
}

void JsonReader::StopStatLoad(Document &result_doc, const StopStat stop_stat, const int req_id) const {
    Document Load(std::istream & input) {
        return Document{LoadNode(input)};
    }
}
