#include "stat_reader.h"

#include <iomanip>
#include <iterator>


void PrintStopStat(std::ostream &output, const StopStat &stop_stat, std::string_view request) {
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

void PrintBusStat(std::ostream &output, const BusStat &bus_stat, std::string_view request) {
    if (bus_stat) {
        output << request << ": " << bus_stat.stop_count << " stops on route, " << bus_stat.uniq_stops
               << " unique stops, " << bus_stat.total_distance << std::setprecision(6) << " route length" << "\n";
    } else {
        output << request << ": not found" << '\n';
    }
}

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
    // Надеюсь правильно понял, что нужно вынести в методы справочника, а не отдельные функции в stat_reader...
    if (command == "Bus") {
        BusStat bus_stat = tansport_catalogue.ReportBusStatistic(req);
        PrintBusStat(output, bus_stat, request);
    }
    // Вывод статистики по запросу остановок
else if (command == "Stop") {
    StopStat stop_stat = tansport_catalogue.ReportStopStatistic(req);
    PrintStopStat(output, stop_stat, request);
}
}

