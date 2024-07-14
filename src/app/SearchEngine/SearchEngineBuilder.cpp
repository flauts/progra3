#include "SearchEngineBuilder.h"
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include "../../tools/Utils.h"


auto stopwords = Utils::loadStopwords("/home/jorughen/Documents/progra3/stopwords.txt");

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