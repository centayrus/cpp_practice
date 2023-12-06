#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    string option;
    is >> option;
    if (option == "NEW_BUS"s) {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        // q.stops.erase();
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
        }
    } else if (option == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (option == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (option == "ALL_BUSES"s) {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    string stop;
    vector<string> buses_for_stops;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    bool is_first = false;
    if (r.stop == ""s) {
        os << "No stop"s;
    } else {
        for (const auto& str : r.buses_for_stops) {
            if (is_first == true) {
                os << " "s;
            }
            os << str;
            is_first = true;
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    if (r.bus == ""s) {
        os << "No bus"s;
    } else {
        bool is_first = true;
        for (const auto& buses : r.stops_for_buses) {
            if (!is_first) {
            os << endl;
            }
            is_first = false;
            os << "Stop "s << buses.first << ":"s;
            if (buses.second.size() == 1) {
                os << " no interchange"s;
            }
            for (const auto& str : buses.second) {
                if (str == r.bus) {
                    continue;
                } else {
                    os << " "s << str;
                }
            }
            
        }
    }
    return os;
}

struct AllBusesResponse {
    vector<pair<string, vector<string>>> all_bus_stops;
};
// вывод всех автобусов и всех остановок
ostream& operator<<(ostream& os, const AllBusesResponse& r) {
            bool is_first = true;

    if (r.all_bus_stops.size() == 0) {
        os << "No buses"s;
    } else {
        for (const auto& line : r.all_bus_stops) {
            if (!is_first) {
            os << endl;
            }
            is_first = false;
            os << "Bus "s << line.first << ":"s;
            for (const auto& str : line.second) {
            
                os << " "s << str;
            }
         //   os << endl;
        }
    }
    return os;
}

class BusManager {
   public:
    // заполнили данными поля автобус-остановки и остановки-автобус.
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops_.insert({bus, stops});

        string local_bus = bus;
        for (const auto& stop_item : stops) {
            stops_to_buses_[stop_item].push_back(local_bus);
        }
    }
    // вывести по названию остановки все проходящие автобусы
    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse resp_struct;
        if (stops_to_buses_.count(stop) == 0) {
            return {""s, {""s}};
        } else {
            resp_struct = {stop, stops_to_buses_.at(stop)};
        }
        return resp_struct;
    }
    // вывести по номеру автобуса пересекающиеся маршруты, если таких нет то no interchange
    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // string bus;
        // vector<pair<string, vector<string>>>
        StopsForBusResponse resp_struct;
        if (buses_to_stops_.count(bus) == 0) {
            return {""s, {{""s, {""s}}}};
        } else {
            for (const auto& stops : buses_to_stops_.at(bus)) {
                resp_struct.stops_for_buses.push_back({stops, stops_to_buses_.at(stops)});
            }
            resp_struct.bus = bus;
        }

        return resp_struct;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse resp;
        for (const auto& f : buses_to_stops_) {
            resp.all_bus_stops.push_back({f.first, f.second});
        }
        return resp;
    }

   private:
    map<string, vector<string>> stops_to_buses_;
    map<string, vector<string>> buses_to_stops_;
};

// void TestAddBus() {
//     BusManager bus_man;
//     istringstream input;
//     // Метод str(строка) у istringstream позволяет задать содержимое, которое будет считываться из istringstream
//     input.str("NEW_BUS 950 6 Kokoshkino Vnukovo"s);
//    // input.str("NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"s);
//     Query q;
//     input >> q;
//     assert(q.type == QueryType::NewBus);
//     assert(q.bus == "950"s);
//     bus_man.AddBus(q.bus, q.stops);
// }

void TestCommon() {
    BusManager bus_man;
    istringstream input;
    ostringstream output;
    Query q;
    output << bus_man.GetAllBuses();
    assert(output.str() == "No buses"s);
    output.str("");
    output << bus_man.GetBusesForStop("Marushkino"s);
    assert(output.str() == "No stop"s);
    output.str("");
    output << bus_man.GetStopsForBus("32K"s);
    assert(output.str() == "No bus"s);
    output.str("");
    input.str("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"s);
    input >> q;
    bus_man.AddBus(q.bus, q.stops);
    input.str("NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo"s);
    input >> q;
    bus_man.AddBus(q.bus, q.stops);
    }


void TestBusManager() {
   // TestAddBus();
    TestCommon();
}

int main() {
    TestBusManager();
    int query_count;
    Query q; 

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}