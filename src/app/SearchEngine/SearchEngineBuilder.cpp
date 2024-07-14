#include "SearchEngineBuilder.h"
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <algorithm>

// Function to load stopwords from a file into a set
std::unordered_set<std::string> loadStopwords(const std::string& filepath) {
    std::unordered_set<std::string> stopwords;
    std::ifstream file(filepath);
    std::string word;
    while (file >> word) {
        stopwords.insert(word);
    }
    return stopwords;
}

std::unordered_set<std::string> stopwords = loadStopwords("C:\\Users\\flauta\\progra3\\proyecto\\progra3\\src\\stopwords.txt");

SearchEngineBuilder &SearchEngineBuilder::Query(const std::string &query) {
    std::stringstream ss(query);
    std::string word;
    std::string filteredQuery;
    while (ss >> word) {
        if (stopwords.find(word) == stopwords.end()) {
            if (!filteredQuery.empty()) {
                filteredQuery += " ";
            }
            filteredQuery += word;
        }
    }
    searchEngine_->query = filteredQuery;
    return *this;
}

SearchEngineBuilder &SearchEngineBuilder::Tags(const std::string &tags) {
    std::stringstream ss(tags);
    std::string t;
    char delimiter = ',';
    while (getline(ss, t, delimiter)) {
        searchEngine_->tags.push_back(t);
    }
    return *this;
}

SearchEngine *SearchEngineBuilder::build() {
    if(searchEngine_->query.empty() and searchEngine_->tags.empty()){
        throw std::runtime_error("Query and tag is empty");
    }
    return searchEngine_;
}