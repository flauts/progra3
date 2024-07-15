#include "SearchEngineBuilder.h"
#include <stdexcept>
#include <sstream>
#include "../../tools/Utils.h"

std::string stopwords_Path = R"(C:\Users\Badir\Documents\projects\Hopium\stopwords.txt)";

SearchEngineBuilder &SearchEngineBuilder::Query(const std::string &query) {
    auto stopwords = Utils::loadStopwords(stopwords_Path);
    std::vector<std::string> words = Utils::splitString(query);
    std::string filtered_query;

    for(const auto& w: words) {
        if (stopwords.find(w) != stopwords.end()) {
            continue;
        }else{
            filtered_query+=w + " ";
        }
    }
    filtered_query.pop_back();
    searchEngine_->query = filtered_query;
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