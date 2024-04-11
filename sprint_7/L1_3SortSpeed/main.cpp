#include <algorithm>
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
        for (int i = 0; i < 20000000; ++i) {
            res.push_back(/* static_cast<int> */ (std::uniform_int_distribution<int>(0, 1000)(engine)));
        }
    }
    {
        LOG_DURATION("ComputeAvgTempForDeque");
        for (int i = 0; i < 20000000; ++i) {
            res_deq.push_back(/* static_cast<int> */ (std::uniform_int_distribution<int>(0, 1000)(engine)));
        }
    }


    {
        LOG_DURATION("ComputeAvgTempSortVector");
        std::sort(res.begin(), res.end());
    }
    {
        LOG_DURATION("ComputeAvgTempSortDeque");
        std::sort(res_deq.begin(), res_deq.end());
    }
    std::cout << "VectorSize: " << res.size() << std::endl;
    std::cout << "DequeSize: " << res_deq.size() << std::endl;
    return 0;
}