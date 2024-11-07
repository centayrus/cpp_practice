#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "json_reader.h"
#include "map_renderer.h"
#include "request_handler.h"

using namespace std;

int main() {

    std::ostringstream out, out1;
    TransportCatalogue catalogue;

    const auto json = json::Load(std::cin);
    auto base_data = json.GetRoot().AsMap().at("base_requests"s).AsArray(); // вектор для заполнения базы
    auto base_req = json.GetRoot().AsMap().at("stat_requests"s).AsArray();  // вектор с запросами
    auto render_node = json.GetRoot().AsMap().at("render_settings"s);       //

    LoadCatalogue(catalogue, base_data);
    RequestHandler req_handler(catalogue);
    RenderSets render_sets;
    FillRenderSets(render_node, render_sets);
    if (!render_sets.validateRenderSets()) {
        throw std::invalid_argument("RenderSets contain invalid argument");
    }
    MapRenderer renderer(render_sets);

    StopPointsSetter(req_handler, renderer);
    auto polyline_set = MakePolylineMap(renderer);
    auto bus_text = MakeBusNameTextMap(renderer);
    auto dot = SetDots(renderer);
    auto stop_text = MakeStopNameTextMap(renderer);

    RenderSchema(polyline_set, renderer);
    RenderSchema(bus_text, renderer);
    RenderSchema(dot, renderer);
    RenderSchema(stop_text, renderer);
    renderer.DocRender(out);

    std::cout << out.str();
}