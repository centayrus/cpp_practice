#include <deque>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "log_duration.h"

int main() {

    static std::mt19937 engine;
    std::vector<int> res;
    std::deque<int> res_deq;
    {
        LOG_DURATION("ComputeAvgTempForVector");
        for (int i = 0; i < 50000000; ++i) {
            res.push_back(/* static_cast<int> */(std::uniform_int_distribution<int>(0, 1000)(engine)));
        }
    }
    {
        LOG_DURATION("ComputeAvgTempForDeque");
        for (int i = 0; i < 50000000; ++i) {
            res_deq.push_back(/* static_cast<int> */(std::uniform_int_distribution<int>(0, 1000)(engine)));
        }
    }
    std::cout << res.size() << std::endl;
    std::cout << res_deq.size() << std::endl;
    return 0;
}