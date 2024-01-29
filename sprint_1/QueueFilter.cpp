#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<string> SplitIntoWords(string text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }



    return words;
}

set<string> MakeSet(vector<string> liters) {
    set<string> s(liters.begin(), liters.end());
    return s;
}

set<string> QueryFiltration(string stop, string query) {
    vector<string> stop_v = SplitIntoWords(stop);
    vector<string> query_v = SplitIntoWords(query);
    set<string> stop_s = MakeSet(stop_v);
    set<string> query_s = MakeSet(query_v);
    set<string> result_set;
    for (string i : query_s) {
        if (!stop_s.count(i)) {
           result_set.insert(i); 
        }
    }
return result_set;
}

int main() {
    /* Считайте строку со стоп-словами */
    string restrict_words;
    getline(cin, restrict_words);
    // Считываем строку-запрос
    string query;
    getline(cin, query);
    
    // Выведите только те слова, которых нет среди стоп-слов
    for (string word : QueryFiltration(restrict_words, query)) {
        cout << '[' << word << ']' << endl;
    }

}