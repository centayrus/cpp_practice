#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

string ReadLine()
{
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber()
{
    int result;
    cin >> result;
    ReadLine();
    return result;
}

int main()
{
    const int queryCount = ReadLineWithNumber();

    vector<string> queries(queryCount);
    for (string &query : queries)
    {
        query = ReadLine();
    }
    const string buzzword = ReadLine();

    cout << count_if(queries.begin(), queries.end(), [buzzword](const string &query)
                     {
           string each_word;
           set<string> query_set;
           for (const char c : query)
    {
        if (c == ' ')
        {
            if (!each_word.empty())
            {
                query_set.insert(each_word);
                each_word.clear();
            }
        }
        else
        {
            each_word += c;
        }
            if (!each_word.empty())
    {
        query_set.insert(each_word);
    }
    }
    return query_set.count(buzzword); });
    cout << endl;
}