#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// enum class Command { CHEER,
//                      READ };

class BookReader {
public:
    BookReader(int user_count, int page_count) {
        readers_progress_.reserve(user_count + 1);
        users_on_page_.reserve(page_count + 1);
        users_on_page_.insert(users_on_page_.end(), page_count + 1, 0);
        readers_progress_.insert(readers_progress_.end(), user_count + 1, -1);
    }

    void SaveReaderProgress(const int &user_id, const int &new_page) {
        auto prev_page = readers_progress_[user_id];
        readers_progress_[user_id] = new_page;
        if (prev_page > -1) {
            users_on_page_[prev_page] -= 1;
            // будем хранить количество уникальных читателей в нулевом элементе
        } else {
            users_on_page_[0] += 1;
        }
        users_on_page_[new_page] += 1;
    }

    double PrintCheerUser(const int &user_id) const {
        if (readers_progress_[user_id] == -1) {
            return 0.;
        }
        int cur_page_num = readers_progress_[user_id];
        double counter = 0.;
        for (int i = 1; i < cur_page_num; ++i) {
                counter += users_on_page_[i];
        }
        if (users_on_page_[0] == 1) {
            return 1.;
        }
        return static_cast<double>(counter) / static_cast<double>(users_on_page_[0] - 1);
    }

private:
    std::vector<int> readers_progress_;
    std::vector<int> users_on_page_;
};

int main() {
    BookReader reader_(100000, 1000);
    int req_count, user_id, page /* , command */;
    std::string command;
    std::cin >> req_count;
    for (int i = 0; i < req_count; ++i) {
        std::cin >> command /* >> user_id >> page */;
        std::cin >> user_id;
        if (command == "READ") {
            std::cin >> page;
            reader_.SaveReaderProgress(user_id, page);
        } else if (command == "CHEER") {
            std::cout << std::setprecision(6) << reader_.PrintCheerUser(user_id) << '\n';
        }
    }
}
