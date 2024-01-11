#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const int MAX_RESULT_DOCUMENT_COUNT = 5;
const double EPS = 1e-6;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

struct Document {

    Document() = default;

    Document(int id, double relevance, int rating)
        : id(id)
        , relevance(relevance)
        , rating(rating) {
    }

    int id = 0;
    double relevance = 0.0;
    int rating = 0;
};

template <typename StringContainer>
set<string> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
    set<string> non_empty_strings;
    for (const string& str : strings) {
        if (!str.empty()) {
            non_empty_strings.insert(str);
        }
    }
    return non_empty_strings;
}

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

template <typename It>
class IteratorRange {
public:
    IteratorRange(It begin, It end, size_t size) 
    : begin_(begin), end_(end)
    {
    }
    It begin() const {
        return begin_;
    }
    It end() const {
        return end_;
    }
    size_t size() const {
        return distance(begin, end);
    }
private:
    It begin_, end_;
};

template <typename It>
class Paginator {
public:
    Paginator(It begin, It end, size_t p_size) {
        int num_pages = (distance(begin, end) + p_size - 1) / p_size;
        for (int i = 0; i < num_pages; ++i) {
            It it_begin = next(begin, p_size * i);
            It it_end = min(begin, next(begin, p_size * (i + 1)));
            pages_.push_back( it_begin, it_end );
        }
    }
    It begin() const {
        return pages_.begin();
    }
    It end() const {
        return pages_.end();
    }
    size_t size() const {
        return pages_.size();
    }
private:
    vector<IteratorRange<It>> pages_;
};

template <typename It>
ostream& operator<<(ostream& out, IteratorRange<It> iterator) {
    for (auto i = iterator.begin(); i != iterator.end(); ++i) {
        out << *i << ' ';
    }
    out << std::endl;
    return out;
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

template <typename Document>
ostream& operator<<(ostream& out, const Document& docs) {
    for (const auto& [id, rel, rat] : docs) {
        out << id << rel << rat << ' ';
    }
    out << std::endl;
    return out;
}

class SearchServer {
public:
    inline static constexpr int INVALID_DOCUMENT_ID = -1;

    template <typename StringContainer>
    explicit SearchServer(const StringContainer& stop_words)
        : stop_words_(MakeUniqueNonEmptyStrings(stop_words)) {
        for (const string& word : MakeUniqueNonEmptyStrings(stop_words)) {
            if (!IsValidWord(word)) {
                throw invalid_argument("Стоп слова содержат недопустимые значения."s);
            }
        }

    }

    explicit SearchServer(const string& stop_words_text)
        : SearchServer(SplitIntoWords(stop_words_text))
    {
    }

    void AddDocument(int document_id, const string& document, DocumentStatus status, const vector<int>& ratings) {
        if (count(doc_count_.begin(), doc_count_.end(), document_id) != 0) {
            throw invalid_argument("Введенный id содержит недопустимое значение: id уже существует."s);
        }
        if (document_id < 0) {
            throw invalid_argument("Введенный id содержит недопустимое значение: id < 0."s);
        }
        const vector<string> words = SplitIntoWordsNoStop(document);
        const double inv_word_count = 1.0 / words.size();
        for (const string& word : words) {
            word_to_document_freqs_[word][document_id] += inv_word_count;
        }
        documents_.emplace(document_id, DocumentData{ ComputeAverageRating(ratings), status });
        doc_count_.push_back(document_id);
    }

    template <typename DocumentPredicate>
    vector<Document> FindTopDocuments(const string& raw_query, DocumentPredicate document_predicate) const {
        const auto query = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query, document_predicate);
        sort(matched_documents.begin(), matched_documents.end(),
            [](const Document& lhs, const Document& rhs) {
                double dif_b_relev = abs(lhs.relevance - rhs.relevance);
                if (dif_b_relev < EPS) {
                    return lhs.rating > rhs.rating;
                }
                return lhs.relevance > rhs.relevance;
            });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }

        return matched_documents;
    }

    vector<Document> FindTopDocuments(const string& raw_query, DocumentStatus status) const {
        return FindTopDocuments(
            raw_query, [status](int document_id, DocumentStatus document_status, int rating) {
                return document_status == status;
            });
    }

    vector<Document> FindTopDocuments(const string& raw_query) const {
        return FindTopDocuments(raw_query, DocumentStatus::ACTUAL);
    }

    int GetDocumentCount() const {
        return documents_.size();
    }

    tuple<vector<string>, DocumentStatus> MatchDocument(const string& raw_query, int document_id) const {
        const auto query = ParseQuery(raw_query);
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
        tuple<vector<string>, DocumentStatus> result = { matched_words, documents_.at(document_id).status };
        return result;
    }

    int GetDocumentId(int index) const {
        if (index < 0 || index >= doc_count_.size()) {
            throw out_of_range("Индекс переданного документа выходит за пределы допустимого диапозона."s);
        }
        return doc_count_.at(index);
    }

private:
    struct DocumentData {
        int rating;
        DocumentStatus status;
    };
    const set<string> stop_words_;
    map<string, map<int, double>> word_to_document_freqs_;
    map<int, DocumentData> documents_;
    vector<int> doc_count_;

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsValidWord(word)) {
                throw invalid_argument("Документ содержит недопустимые значения."s);
            }
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
        int rating_sum = accumulate(ratings.begin(), ratings.end(), 0);
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
        if (!IsValidWord(text)) {
            throw invalid_argument("Запрос содержит недопустимые значения."s);
        }
        if (text[0] == '-' && !text.empty()) {
            if (text[1] == '-') {
                throw invalid_argument("Запрос содержит недопустимые значения: наличие более одного минуса."s);
            }
            is_minus = true;
            text = text.substr(1);
        }
        QueryWord query = { text, is_minus, IsStopWord(text) };
        return query;

    }

    struct Query {
        set<string> plus_words;
        set<string> minus_words;
    };

    Query ParseQuery(const string& text) const {
        Query query;
        for (const string& word : SplitIntoWords(text)) {
            const auto query_word = ParseQueryWord(word);
            if (query_word.data.empty()) {
                throw invalid_argument("Запрос содержит недопустимые значения: пустое значение."s);
            }
            if (!query_word.is_stop) {
                if (query_word.is_minus) {
                    query.minus_words.insert(query_word.data);
                }
                else {
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

    template <typename DocumentPredicate>
    vector<Document> FindAllDocuments(const Query& query,
        DocumentPredicate document_predicate) const {
        map<int, double> document_to_relevance;
        for (const string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
            for (const auto [document_id, term_freq] : word_to_document_freqs_.at(word)) {
                const auto& document_data = documents_.at(document_id);
                if (document_predicate(document_id, document_data.status, document_data.rating)) {
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
                { document_id, relevance, documents_.at(document_id).rating });
        }
        return matched_documents;
    }

    static bool IsValidWord(const string& word) {
        return none_of(word.begin(), word.end(), [](char c) {
            return c >= '\0' && c < ' ';
            });
    }

};

// ==================== для примера =========================


int main() {
    SearchServer search_server("and with"s);
    search_server.AddDocument(1, "funny pet and nasty rat"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "funny pet with curly hair"s, DocumentStatus::ACTUAL, { 1, 2, 3 });
    search_server.AddDocument(3, "big cat nasty hair"s, DocumentStatus::ACTUAL, { 1, 2, 8 });
    search_server.AddDocument(4, "big dog cat Vladislav"s, DocumentStatus::ACTUAL, { 1, 3, 2 });
    search_server.AddDocument(5, "big dog hamster Borya"s, DocumentStatus::ACTUAL, { 1, 1, 1 });
    const auto search_results = search_server.FindTopDocuments("curly dog"s);
    int page_size = 2;  
    const auto pages = Paginate(search_results, page_size);
    // Выводим найденные документы по страницам
    for (auto page = pages.begin(); page != pages.end(); ++page) {
        cout << *page << endl;
       // cout << "Page break"s << endl;
    }
}
