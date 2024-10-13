#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "json_reader.h"
#include "request_handler.h"

using namespace std;

int main() {

    std::ostringstream out;
    TransportCatalogue catalogue;

    const auto json = json::Load(std::cin);
    auto base_data = json.GetRoot().AsMap().at("base_requests"s).AsArray(); // вектор для заполнения базы
    auto base_req = json.GetRoot().AsMap().at("stat_requests"s).AsArray();  // вектор с запросами
    auto render_node = json.GetRoot().AsMap().at("render_settings"s);  // 

    LoadCatalogue(catalogue, base_data);
    RequestHandler req_handler(catalogue);

    RenderSets render_sets;
    FillRenderSets(render_node, render_sets);

}