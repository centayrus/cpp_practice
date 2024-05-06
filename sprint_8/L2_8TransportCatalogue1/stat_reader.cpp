#include "stat_reader.h"

#include <iterator>

void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request,
                       std::ostream& output) {
  //  std::string_view req = Trim(request);
    std::string req;
    size_t pos_first = 0;
    pos_first = request.find_first_of(' ', pos_first);
    size_t pos_last = request.find_last_not_of(' ', pos_first);
    req = request.substr(pos_first+1, pos_last-pos_first-1);
    BusStat bus_stat = tansport_catalogue.FindBus(req);
    output << request << ": " << bus_stat.stop_count << "  stops on route, " << bus_stat.uniq_stops 
    << " unique stops, " << bus_stat.total_distance << " route length";
    //Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length
}