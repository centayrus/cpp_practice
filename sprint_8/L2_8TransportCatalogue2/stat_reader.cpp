#include "stat_reader.h"

#include <iomanip>
#include <iterator>

void ParseAndPrintStat(const TransportCatalogue &tansport_catalogue, std::string_view request,
                       std::ostream &output) {
    std::string_view req;
    size_t pos_first = 0;
    pos_first = request.find_first_not_of(' ', pos_first);
    size_t pos_second = request.find_first_of(' ', pos_first);
    std::string_view command = request.substr(pos_first, pos_second - pos_first);
    size_t pos_last = request.find_last_not_of(' ', pos_second);
    req = request.substr(pos_second + 1, pos_last - pos_second - 1);

    // Вывод статистики по запросу маршрутов
    if (command == "Bus") {
        BusStat bus_stat = tansport_catalogue.FindBus(req);

        if (bus_stat) {
            output << request << ": " << bus_stat.stop_count << " stops on route, " << bus_stat.uniq_stops
                   << " unique stops, " << bus_stat.total_distance << std::setprecision(6) << " route length" << "\n";
        } else {
            output << request << ": not found" << '\n';
        }
        // Вывод статиситки по запросу остановок
    } else if (command == "Stop") {
        StopStat stop_stat = tansport_catalogue.GetStopStat(req);
        output << request;
        if (!stop_stat) {
            output << ": not found" << '\n';
        } else {
            if (stop_stat.bus_routes.size() == 0) {
                output << ": no buses" << '\n';
            } else {
                output << ": buses";
                for (auto it = stop_stat.bus_routes.begin(); it != stop_stat.bus_routes.end(); ++it) {
                    output << " " << (*it)->bus_route;
                }
                output << '\n';
            }
        }
    }
}