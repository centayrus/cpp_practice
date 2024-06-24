#pragma once

#include <iosfwd>
#include <string_view>

#include "transport_catalogue.h"

void ParseAndPrintStat(const TransportCatalogue &tansport_catalogue, std::string_view request,
                       std::ostream &output);

void PrintStopStat(std::ostream &output, const StopStat &stop_stat, std::string_view request);

void PrintBusStat(std::ostream &output, const BusStat &bus_stat, std::string_view request);