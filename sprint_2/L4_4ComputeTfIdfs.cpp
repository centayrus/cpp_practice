#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <typename Documents, typename Term>

vector<double> ComputeTfIdfs(const Documents &documents, const Term &query) {
    int count;
    double idf;
    vector<double> tf_line, result;
    for (const auto &doc : documents) {
        count = count_if(doc.begin(), doc.end(), [&query](const auto &doc) {
            return query == doc;
        });
        tf_line.push_back(count / static_cast<double>(doc.size()));
    }
    double non_zero = count_if(
        tf_line.begin(), tf_line.end(), [](const double &tf) {
            return tf > 0;
        });
    idf = log(static_cast<double>(documents.size()) / non_zero);
    for (const auto &tf : tf_line) {
        result.push_back(tf * idf);
    }
    return result;
}

int main() {
    const vector<vector<string>> documents = {
        {"белый"s, "кот"s, "и"s, "модный"s, "ошейник"s},
        {"пушистый"s, "кот"s, "пушистый"s, "хвост"s},
        {"ухоженный"s, "пёс"s, "выразительные"s, "глаза"s},
    };
    const auto &tf_idfs = ComputeTfIdfs(documents, "кот"s);
    for (const double tf_idf : tf_idfs) {
        cout << tf_idf << " "s;
    }
    cout << endl;
    return 0;
}