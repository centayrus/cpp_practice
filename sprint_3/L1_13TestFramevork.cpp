#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

vector<string> SplitIntoWords(const string& text) {
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

struct Document {
    int id;
    double relevance;
    int rating;
};

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

class SearchServer {
   public:
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }

    void AddDocument(int document_id, const string& document, DocumentStatus status,
                     const vector<int>& ratings) {
        const vector<string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size();
        for (const string& word : words) {
            word_to_document_freqs_[word][document_id] += inv_word_count;
        }
        documents_.emplace(document_id, DocumentData{ComputeAverageRating(ratings), status});
    }

    // шаблонная функция, в параметр которой передается функция-предикат для динамической фильтрации
    template <typename Predicate>
    vector<Document> FindTopDocuments(const string& raw_query,
                                      Predicate predicate) const {
        const Query query = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query, predicate);  // struct Document {int id; double relevance; int rating;};

        sort(matched_documents.begin(), matched_documents.end(),
             [](const Document& lhs, const Document& rhs) {
                 if (abs(lhs.relevance - rhs.relevance) < 1e-6) {
                     return lhs.rating > rhs.rating;
                 } else {
                     return lhs.relevance > rhs.relevance;
                 }
             });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

    // вызывается, когда в функцию второй параметр передается конкретный статус документа
    vector<Document> FindTopDocuments(const string& raw_query, DocumentStatus doc_status) const {
        return FindTopDocuments(raw_query, [doc_status](int document_id, DocumentStatus status, int rating) { return status == doc_status; });
    }

    // вызывется, когда в метод передается один параметр
    vector<Document> FindTopDocuments(const string& raw_query) const {
        return FindTopDocuments(raw_query, DocumentStatus::ACTUAL);
    }

    int GetDocumentCount() const {
        return documents_.size();
    }

    tuple<vector<string>, DocumentStatus> MatchDocument(const string& raw_query,
                                                        int document_id) const {
        const Query query = ParseQuery(raw_query);
        vector<string> matched_words;
        for (const string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            if (word_to_document_freqs_.at(word).count(document_id)) {
                matched_words.push_back(word);
            }
        }
        for (const string& word : query.minus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            if (word_to_document_freqs_.at(word).count(document_id)) {
                matched_words.clear();
                break;
            }
        }
        return {matched_words, documents_.at(document_id).status};
    }

   private:
    struct DocumentData {
        int rating;
        DocumentStatus status;
    };

    set<string> stop_words_;
    map<string, map<int, double>> word_to_document_freqs_;
    map<int, DocumentData> documents_;

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    static int ComputeAverageRating(const vector<int>& ratings) {
        if (ratings.empty()) {
            return 0;
        }
        int rating_sum = 0;
        for (const int rating : ratings) {
            rating_sum += rating;
        }
        return rating_sum / static_cast<int>(ratings.size());
    }

    struct QueryWord {
        string data;
        bool is_minus;
        bool is_stop;
    };

    QueryWord ParseQueryWord(string text) const {
        bool is_minus = false;
        // Word shouldn't be empty
        if (text[0] == '-') {
            is_minus = true;
            text = text.substr(1);
        }
        return {text, is_minus, IsStopWord(text)};
    }

    struct Query {
        set<string> plus_words;
        set<string> minus_words;
    };

    Query ParseQuery(const string& text) const {
        Query query;
        for (const string& word : SplitIntoWords(text)) {
            const QueryWord query_word = ParseQueryWord(word);
            if (!query_word.is_stop) {
                if (query_word.is_minus) {
                    query.minus_words.insert(query_word.data);
                } else {
                    query.plus_words.insert(query_word.data);
                }
            }
        }
        return query;
    }

    // Existence required
    double ComputeWordInverseDocumentFreq(const string& word) const {
        return log(GetDocumentCount() * 1.0 / word_to_document_freqs_.at(word).size());
    }

    template <typename Predicate>
    vector<Document> FindAllDocuments(const Query& query, Predicate predicate) const {
        map<int, double> document_to_relevance;
        for (const string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
            for (const auto [document_id, term_freq] : word_to_document_freqs_.at(word)) {
                if (predicate(document_id, documents_.at(document_id).status, documents_.at(document_id).rating))

                {
                    document_to_relevance[document_id] += term_freq * inverse_document_freq;
                }
            }
        }

        for (const string& word : query.minus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            for (const auto [document_id, _] : word_to_document_freqs_.at(word)) {
                document_to_relevance.erase(document_id);
            }
        }

        vector<Document> matched_documents;
        for (const auto [document_id, relevance] : document_to_relevance) {
            matched_documents.push_back(
                {document_id, relevance, documents_.at(document_id).rating});
        }
        return matched_documents;
    }
};

/*
   Подставьте сюда вашу реализацию макросов
   ASSERT, ASSERT_EQUAL, ASSERT_EQUAL_HINT, ASSERT_HINT и RUN_TEST
*/

#define ASSERT_EQUAL(x, y) AssertEqualImpl((x), (y), #x, #y, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_EQUAL_HINT(x, y, z) AssertEqualHintImpl((x), (y), #x, #y, __FILE__, __FUNCTION__, __LINE__, z)
#define ASSERT_HINT(x, z) AssertHint((x), #x, __FILE__, __FUNCTION__, __LINE__, z)
#define ASSERT(x) Assert((x), #x, __FILE__, __FUNCTION__, __LINE__)
#define RUN_TEST(func)

 // разделил функции с hint и без hint, хотя можно было и не делать это
template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file, const string& func, unsigned line) {
    if (t != u) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
       // cerr << t << " != "s << u << "."s;
        cerr << endl;
        abort();
    }
}

template <typename T, typename U>
void AssertEqualHintImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file, const string& func, unsigned line, const string& hint) {
    if (t != u) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_EQUAL_HINT("s << t_str << ", "s << u_str << ") failed: "s;
        cerr << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

template <typename T>
void AssertHint(const T& t, const string& t_str, const string& file, const string& func, unsigned line, const string& hint) {
    if (!t) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_HINT("s << t_str << ") failed: "s;
        cerr << t << " != "s << "true"s << "."s;
        if (!hint.empty()) {
            cout << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

template <typename T>
void Assert(const T& t, const string& t_str, const string& file, const string& func, unsigned line) {
    if (!t) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT("s << t_str << ") failed: "s;
        cerr << t << " != "s<< "true"s << "."s;
        cerr << endl;
        abort();
    }
}

// -------- Начало модульных тестов поисковой системы ----------

// Тест проверяет, что поисковая система исключает стоп-слова при добавлении документов
void TestExcludeStopWordsFromAddedDocumentContent() {
    const int doc_id = 42;
    const string content = "cat in the city"s;
    const vector<int> ratings = {1, 2, 3};
    {
        SearchServer server;
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        const auto found_docs = server.FindTopDocuments("in"s);
        ASSERT_EQUAL(found_docs.size(), 1u);
        const Document& doc0 = found_docs[0];
        ASSERT_EQUAL(doc0.id, doc_id);
    }

    {
        SearchServer server;
        server.SetStopWords("in the"s);
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        ASSERT_HINT(server.FindTopDocuments("in"s).empty(),
                    "Stop words must be excluded from documents"s);
    }

    {
        SearchServer server;
        // server.SetStopWords("in the"s);
        server.AddDocument(doc_id, content, DocumentStatus::ACTUAL, ratings);
        ASSERT(server.FindTopDocuments("-in cat"s).empty());
    }
}


vector<int> GetVectorFromStruct(const vector<Document>& docs) {
    vector<int> relevance_vec;
    for (const auto& [id, relevance, rating] : docs) {
        relevance_vec.push_back(id);
    }
    return relevance_vec;
}

void TestCheckRating() {
    const double EPSILON = 1e-6;
    SearchServer server;
    server.SetStopWords("и в на"s);
    server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, {8, -3});
    server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::ACTUAL, {7, 2, 7});
    server.AddDocument(2, "ухоженный пёс выразительные глаза"s, DocumentStatus::ACTUAL, {5, -12, 2, 1});
    server.AddDocument(3, "ухоженный скворец евгений"s, DocumentStatus::BANNED, {9});
    const auto doc1 = server.FindTopDocuments("пушистый ухоженный кот"s, DocumentStatus::BANNED);
    ASSERT_EQUAL_HINT(doc1[0].rating, static_cast<int>(9), "Not correct rating rating for BANNED DOC"s);
   // ASSERT_HINT(abs(doc1[0].relevance - static_cast<double>(0.231049)) < EPSILON, "Not correct relevance for BANNED DOC"s);
    const auto doc2 = server.FindTopDocuments("пушистый ухоженный кот"s, [](int document_id, DocumentStatus status, int rating) { return document_id % 2 == 0; });
    ASSERT_HINT(abs(doc2.front().relevance - static_cast<double>(0.173287)) < EPSILON, "Not correct relevance for predicate"s);
   // const auto doc3 = server.FindTopDocuments("пушистый -ухоженный кот"s, DocumentStatus::ACTUAL);
   // ASSERT_HINT(static_cast<int>(doc3.size()) != static_cast<int>(2), "Not correct doc_id"s);
    vector<int> doc_reference = {1, 0, 2};
    const auto doc4 = server.FindTopDocuments("пушистый ухоженный кот"s);
    ASSERT_EQUAL(GetVectorFromStruct(doc4), doc_reference);
}

// DocumentStatus GetDocumentStat(const tuple<vector<string>, DocumentStatus>& doc_tuple) {
//       DocumentStatus doc_st;
//       for (const auto& l : get<1>(doc_tuple).front()) {       doc_st = l;
//       }
// }



    void TestMatchedDocuments() {
        SearchServer server;
    server.SetStopWords("и в на"s);
    server.AddDocument(0, "белый кот и модный ошейник"s, DocumentStatus::ACTUAL, {8, -3});
    server.AddDocument(1, "пушистый кот пушистый хвост"s, DocumentStatus::BANNED, {7, 2, 7});
    const auto match_doc_tuple = server.MatchDocument("пушистый -модный кот"s, 0);
    ASSERT(get<0>(match_doc_tuple).size() == 0u);
    const auto match_doc_tuple2 = server.MatchDocument("пушистый модный кот"s, 1);
    ASSERT(get<1>(match_doc_tuple2) == DocumentStatus::BANNED);
    }

/*
Разместите код остальных тестов здесь
*/

// Функция TestSearchServer является точкой входа для запуска тестов
void TestSearchServer() {
    RUN_TEST(TestExcludeStopWordsFromAddedDocumentContent);
    RUN_TEST(TestCheckRating);
    RUN_TEST(TestMatchedDocuments);
    // RUN_TEST(TestGetFirstDocument);
    //  Не забудьте вызывать остальные тесты здесь
}

// --------- Окончание модульных тестов поисковой системы -----------

int main() {
    TestSearchServer();
    // Если вы видите эту строку, значит все тесты прошли успешно
    cout << "Search server testing finished"s << endl;
}