#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "log_duration.h"

using namespace std;

struct AvgTemp {
    float temp;
    long unsigned int count;
};

vector<float> ComputeAvgTemp(const vector<vector<float>> &measures) {
    vector<float> result;
    if (!measures.size()) {
        return result;
    }
    long unsigned int m = measures.size();
    result.reserve(m);
    vector<AvgTemp> at;
    
at.reserve(measures[0].size());
    for (long unsigned int j = 0; j < m; ++j) {
        long unsigned int n = measures[j].size();
        at[j].temp = 0.f;
        at[j].count = 1;
        for (long unsigned int i = 0; i < n; ++i) {
          at[i].temp += (measures[j][i] > 0.f ? measures[j][i] : 0.f);
        at[i].count += (measures[j][i] > 0.f ? 1 : 0);
        
            }
       // result.push_back(at[i].temp/at[i].count);   
      
        }

cout << result.size() << endl;
for (auto i : at) {
    
    result.push_back(i.temp / i.count);
    //cout << "result: " << *i << endl;
}
          return result;
}

vector<float> GetRandomVector(int size) {
   // static mt19937 engine;
   // uniform_real_distribution<float> d(-100, 100);

    vector<float> res(size);
    for (int i = 0; i < size; ++i) {
       // res[i] = d(engine);
       res[i] = 1.f;
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