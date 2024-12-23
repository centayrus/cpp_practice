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
    std::ostringstream out;
    TransportCatalogue catalogue;

    const auto json = json::Load(std::cin);
    auto base_data = json.GetRoot().AsDict().at("base_requests"s).AsArray();      // вектор для заполнения базы
    auto base_req = json.GetRoot().AsDict().at("stat_requests"s).AsArray();       // вектор с запросами, в ответ на него возвращается статистика
    auto render_node = json.GetRoot().AsDict().at("render_settings"s).AsDict();   // свойства для отрисовки
    auto routing_node = json.GetRoot().AsDict().at("routing_settings"s).AsDict(); // свойство ожидания и скорости движения
                                                   
    LoadCatalogue(catalogue, base_data);
    // передаем в класс построения маршрута константную ссылку на каталог и мапу сеттингов

    router::TransportRouter router(catalogue, routing_node.at("bus_wait_time").AsInt(), routing_node.at("bus_velocity").AsDouble());

    RequestHandler req_handler(catalogue, router);
    RenderSets render_sets;
    FillRenderSets(render_node, render_sets);

    MapRenderer renderer(render_sets);

    json::Document doc = GetReqsResults(req_handler, base_req, renderer);
    json::Print(doc, out);

    std::cout << out.str();
}

// https://tfcp.ru/ru/%D0%A0%D0%B0%D0%B7%D0%B4%D0%B5%D0%BB%E2%84%963-1/%D0%B3%D1%80%D0%B0%D1%84%D1%8B-%D0%BE%D0%B1%D1%85%D0%BE%D0%B4-%D0%B2-%D0%B3%D0%BB%D1%83%D0%B1%D0%B8%D0%BD%D1%83-%D1%88%D0%B8%D1%80%D0%B8%D0%BD%D1%83
// https://nuancesprog-ru.turbopages.org/nuancesprog.ru/s/p/9269/