
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

class HotelManager {
public:
    void Book(const int64_t& time, const string &hotel_name, const int& client_id, const int& room_count) {
        auto t = std::make_tuple(std::move(time), std::move(client_id), std::move(room_count));
        db_[std::move(hotel_name)].push_back(t);
        if (current_time_ < time) {
            current_time_ = time;
        }
    }
    int ComputeClientCount(const std::string &command) const {
        auto it = db_.find(std::move(command));
        if (it == db_.end()) {
            return 0;
        }
        std::set<int> clients_count;
        for (auto item : it->second) {
            if (get<0>(item) > current_time_ - 86400) {
                clients_count.insert(get<1>(item));
            }
        }
        return static_cast<int>(clients_count.size());
    }
    int ComputeRoomCount(const std::string &command) const {
        auto it = db_.find(std::move(command));
        if (it == db_.end()) {
            return 0;
        }
        int room_count = 0;
        for (auto item : it->second) {
            if (get<0>(item) > current_time_ - 86400) {
                room_count += get<2>(item);
            }
        }
    return room_count;
    }

private:
    std::map<std::string, std::vector<std::tuple<int64_t, int, int>>> db_;
    int current_time_ = 0;
};

int main() {
    HotelManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            int client_id, room_count;
            cin >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS") {
                cout << manager.ComputeClientCount(hotel_name) << "\n";
            } else if (query_type == "ROOMS") {
                cout << manager.ComputeRoomCount(hotel_name) << "\n";
            }
        }
    }

    return 0;
}