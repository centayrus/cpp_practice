#include "json_builder.h"
#include <iostream>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "json_reader.h"
#include "map_renderer.h"
#include "request_handler.h"

using namespace std;

int main() {
   /* json::Print(
        json::Document{
            json::Builder{}
            .StartDict()
                .Key("key1"s).Value(123)
                .Key("key2"s).Value("value2"s)
                .Key("key3"s).StartArray()
                    .Value(456)
                    .StartDict().EndDict()
                    .StartDict()
                        .Key(""s)
                        .Value(nullptr)
                    .EndDict()
                    .Value(""s)
                .EndArray()
            .EndDict()
            .Build()
        },
        cout
    );
    cout << endl;
    
    json::Print(
        json::Document{
            json::Builder{}
            .Value("just a stringgggg"s)
            .Build()
        },
        cout
    ); */
    
    std::ostringstream out;
    TransportCatalogue catalogue;

    const auto json = json::Load(std::cin);
    auto base_data = json.GetRoot().AsDict().at("base_requests"s).AsArray(); // вектор для заполнения базы
    auto base_req = json.GetRoot().AsDict().at("stat_requests"s).AsArray();  // вектор с запросами, в ответ на него возвращается статистика
    auto render_node = json.GetRoot().AsDict().at("render_settings"s);       // свойства для отрисовки

    LoadCatalogue(catalogue, base_data);
    RequestHandler req_handler(catalogue);
    RenderSets render_sets;
    FillRenderSets(render_node, render_sets);
    if (!render_sets.validateRenderSets()) {
        throw std::invalid_argument("RenderSets contain invalid argument");
    }
    MapRenderer renderer(render_sets);

    json::Document doc = GetReqsResults(req_handler, base_req, renderer);
    json::Print(doc, out);

     std::cout << out.str();
}
   
