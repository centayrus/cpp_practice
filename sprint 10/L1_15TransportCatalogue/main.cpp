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
    auto render_node = json.GetRoot().AsMap().at("render_settings"s);       //

    LoadCatalogue(catalogue, base_data);
    RequestHandler req_handler(catalogue);

    RenderSets render_sets;
    FillRenderSets(render_node, render_sets);
    if (!render_sets.validateRenderSets()) {
        throw std::invalid_argument("RenderSets contain invalid argument");
    }
    MapRenderer map_renderer(render_sets);
    auto buses = req_handler.GetUniqueStops();
    auto min_coord = FindMinCoordinates(buses);
    auto max_coord = FindMaxCoordinates(buses);

    SphereProjector point_mapper(min_coord, max_coord, render_sets.width, render_sets.height, render_sets.padding);
    
    сделать так: 
        Circle c;
    c.SetRadius(3.5).SetCenter({1.0, 2.0});
    c.SetFillColor(rgba);
    c.SetStrokeColor(purple);
    
    Document doc;
    doc.Add(std::move(c));
    doc.Render(cout);
}