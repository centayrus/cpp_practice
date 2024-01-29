#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Document {
    int id;
    int rating;
};

bool SortVector(const Document elem1, const Document elem2) {
    return elem1.rating > elem2.rating;
}

void PrintDocuments(vector<Document> documents, size_t skip_start, size_t skip_finish)
 {
    // отсортировать документы и вывести не все
    sort(documents.begin(), documents.end(), SortVector);
    size_t count = documents.size();
    for (size_t i = 0; i < count; ++i) {
       // cout << "i = "s << i << endl; 
       // cout << "static_cast<int>(count)-static_cast<int>(skip_finish)-1 = "s << static_cast<int>(count)-static_cast<int>(skip_finish)-1 << endl;
        if (i < skip_start || static_cast<int>(i) > (static_cast<int>(count)-static_cast<int>(skip_finish)-1)) {
            continue;
        }
        cout << "{ id = "s << documents[i].id << ", rating = "s << documents[i].rating << " }"s << endl;
    }

}

int main() {
    PrintDocuments({{100, 5}, {101, 7}, {102, -4}, {103, 9}, {104, 1}}, 1, 100
    );
}