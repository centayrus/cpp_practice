#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "log_duration.h"

using namespace std;

struct AvgTemp {
    float temp = 0.f;
    long unsigned int count = 0;
};

vector<float> ComputeAvgTemp(const vector<vector<float>> &measures) {
    vector<float> result;
    if (!measures.size()) {
        return result;
    }
    long unsigned int m = measures.size();
    long unsigned int n = measures[0].size();
    vector<AvgTemp> temp_temp;
    temp_temp.reserve(n);
    result.reserve(n);

    for (long unsigned int j = 0; j < m; ++j) {
        for (long unsigned int i = 0; i < n; ++i) {
            temp_temp[i].temp += (measures[j][i] > 0.f ? measures[j][i] : 0.f);
            temp_temp[i].count += (measures[j][i] > 0.f ? 1 : 0);
        }
    }
    for (size_t i = 0; i < n; ++i) {
        result.push_back(temp_temp[i].temp / (temp_temp[i].count == 0 ? 1 : temp_temp[i].count));
    }
    return result;
}

vector<float> GetRandomVector(int size) {
    static mt19937 engine;
    uniform_real_distribution<float> d(-100, 100);

    vector<float> res(size);
    for (int i = 0; i < size; ++i) {
        res[i] = d(engine);
    }

    return res;
}

int main() {
    vector<vector<float>> data;
    data.reserve(50);

    for (int i = 0; i < 50; ++i) {
        data.push_back(GetRandomVector(30));
    }

    vector<float> avg;
    {
        LOG_DURATION("ComputeAvgTemp"s);
        avg = ComputeAvgTemp(data);
    }

    cout << "Total mean: "s << accumulate(avg.begin(), avg.end(), 0.f) / avg.size() << endl;
}