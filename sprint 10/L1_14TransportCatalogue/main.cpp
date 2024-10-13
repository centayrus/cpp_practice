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

    const auto json = json::Load(std::cin);                                 //.GetRoot().AsMap();
    auto base_data = json.GetRoot().AsMap().at("base_requests"s).AsArray(); // это вектор для заполнения базы
    auto base_req = json.GetRoot().AsMap().at("stat_requests"s).AsArray();  // это вектор с запросами.

    LoadCatalogue(catalogue, base_data);
    RequestHandler req_handler(catalogue);

    json::Document doc = GetReqsResults(req_handler, base_req);

    json::Print(doc, out);

    std::cout << out.str();
}