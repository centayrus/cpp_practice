#include <algorithm>
#include <sstream>
#include <vector>

#include "json_reader.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из JSON,
 * а также код обработки запросов к базе и формирование массива ответов в формате JSON
 */

void LoadCatalogue(TransportCatalogue &db, const std::vector<json::Node> &base_req) {
    std::vector<json::Node> array_copy;
    // копирование array, чтобы обойти константность при сортировке
    for (auto const &item : base_req) {
        if (item.AsMap().at("type").AsString() == "Stop")
            array_copy.push_back(item);
    }
    for (auto const &item : base_req) {
        if (item.AsMap().at("type").AsString() == "Bus")
            array_copy.push_back(item);
    }
    for (const auto &item : array_copy) {
        if (item.AsMap().at("type").AsString() == "Stop") {
            db.AddStop(item.AsMap().at("name").AsString(), {item.AsMap().at("latitude").AsDouble(), item.AsMap().at("longitude").AsDouble()});
        } else {
            std::vector<std::string_view> string_vec;
            for (const auto &node1 : item.AsMap().at("stops").AsArray()) {
                string_vec.emplace_back(node1.AsString());
            }
            if (!item.AsMap().at("is_roundtrip").AsBool()) {
                string_vec.insert(string_vec.end(), std::next(string_vec.rbegin()), string_vec.rend());
            }
            db.AddBus(item.AsMap().at("name").AsString(), string_vec);
        }
    }
    for (const auto &stop : array_copy) {
        if (stop.AsMap().at("type").AsString() == "Stop") {
            for (const auto &stop_list : stop.AsMap().at("road_distances").AsMap()) {
                db.SetDistance(stop.AsMap().at("name").AsString(), stop_list.first, stop_list.second.AsInt());
            }
        }
    }
}

json::Document GetReqsResults(const RequestHandler &req_handler, const std::vector<json::Node> &base_req) {
    std::istringstream strm("[]");
    json::Document result_doc = json::Load(strm);
    json::Node tmp_node;
    for (auto &req : base_req) {
        auto req_id = req.AsMap().at("id").AsInt();
        if (req.AsMap().at("type").AsString() == "Stop") {
            StopStat stop_stat = req_handler.GetBusesByStop(req.AsMap().at("name").AsString());
            tmp_node = StopStatLoad(std::move(stop_stat), req_id);
        } else {
            BusStat bus_stat = req_handler.GetBusStat(req.AsMap().at("name").AsString());
            tmp_node = BusStatLoad(std::move(bus_stat), req_id);
        }
        const_cast<std::vector<json::Node> &>(result_doc.GetRoot().AsArray()).push_back(tmp_node);
    }
    return result_doc;
}

json::Node BusStatLoad(const BusStat bus_stat, const int req_id) {
    std::string json_str;
    if (!bus_stat) {
        json_str += "{\"request_id\":";
        json_str += std::to_string(req_id);
        json_str += ",\"error_message\": \"not found\"}";
    } else {
        json_str += "{\"curvature\":";
        json_str += std::to_string(bus_stat.dist_proportion);
        json_str += ",\"request_id\":";
        json_str += std::to_string(req_id);
        json_str += ",\"route_length\":";
        json_str += std::to_string(bus_stat.total_distance);
        json_str += ",\"stop_count\":";
        json_str += std::to_string(bus_stat.stop_count);
        json_str += ",\"unique_stop_count\":";
        json_str += std::to_string(bus_stat.uniq_stops);
        json_str += "}";
    }
    std::istringstream strm(json_str);
    json::Document doc_item = json::Load(strm);
    return doc_item.GetRoot();
}

json::Node StopStatLoad(const StopStat stop_stat, const int req_id) {
    std::string json_str;
    if (!stop_stat) {
        json_str += "{\"request_id\":";
        json_str += std::to_string(req_id);
        json_str += ",\"error_message\": \"not found\"}";
    } else {
        json_str += "{\"buses\": [";
        bool is_first = true;
        for (const auto *bus : stop_stat.bus_routes) {

            if (!is_first) {
                json_str += ",";
            }
            json_str += "\"";
            json_str += bus->bus_route;
            json_str += "\"";
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

void FillRenderSets(const json::Node &render_node, RenderSets &render_sets) {
    json::Dict attrs = render_node.AsMap();
    render_sets.width = attrs.at("width").AsDouble();
    render_sets.height = attrs.at("height").AsDouble();
    render_sets.padding = attrs.at("padding").AsDouble();
    render_sets.line_width = attrs.at("line_width").AsDouble();
    render_sets.stop_radius = attrs.at("stop_radius").AsDouble();
    render_sets.bus_label_font_size = attrs.at("bus_label_font_size").AsInt();
    render_sets.bus_label_offset = svg::Point(attrs.at("bus_label_offset").AsArray()[0].AsDouble(), attrs.at("bus_label_offset").AsArray()[1].AsDouble());
    render_sets.stop_label_font_size = attrs.at("stop_label_font_size").AsInt();
    render_sets.stop_label_offset = svg::Point(attrs.at("stop_label_offset").AsArray()[0].AsDouble(), attrs.at("stop_label_offset").AsArray()[1].AsDouble());
    render_sets.underlayer_color = svg::Rgba(static_cast<uint8_t>(attrs.at("underlayer_color").AsArray()[0].AsInt()),
                                             static_cast<uint8_t>(attrs.at("underlayer_color").AsArray()[1].AsInt()),
                                             static_cast<uint8_t>(attrs.at("underlayer_color").AsArray()[2].AsInt()),
                                             static_cast<uint8_t>(attrs.at("underlayer_color").AsArray()[3].AsDouble()));
    render_sets.underlayer_width = attrs.at("underlayer_width").AsDouble();
    for (const auto &item : attrs.at("color_palette").AsArray()) {
        if (item.IsString()) {
            render_sets.color_palette.push_back(item.AsString());
        } else if (item.IsArray()) {
            auto rgb = svg::Rgb(static_cast<uint8_t>(item.AsArray()[0].AsInt()),
                                static_cast<uint8_t>(item.AsArray()[1].AsInt()), static_cast<uint8_t>(item.AsArray()[2].AsInt()));
            render_sets.color_palette.push_back(rgb);
        }
    }
    if (render_sets.validateRenderSets()) {
        throw std::invalid_argument("Render set attrs is not valid");
    }
}

geo::Coordinates FindMinCoordinates(const std::deque<Stop> &buses) {
    double min_lat, min_lon;
    bool is_first = true;
    for (const auto &bus : buses) {
        if (is_first) {
            min_lat = bus.coordinate.lat;
            min_lon = bus.coordinate.lon;
            is_first = false;
        }
        if (bus.coordinate.lat < min_lat) {
            min_lat = bus.coordinate.lat;
        }
        if (bus.coordinate.lon < min_lon) {
            min_lon = bus.coordinate.lon;
        }
    }
}

geo::Coordinates FindMaxCoordinates(const std::deque<Stop> &buses) {
    double min_lat, min_lon, max_lat, max_lon;
    bool is_first = true;
    for (const auto &bus : buses) {
        if (is_first) {
            max_lat = bus.coordinate.lat;
            max_lon = bus.coordinate.lon;
            ;
            is_first = false;
        }
        if (bus.coordinate.lat > max_lat) {
            max_lat = bus.coordinate.lat;
        }
        if (bus.coordinate.lon > max_lon) {
            max_lon = bus.coordinate.lon;
        }
    }
}