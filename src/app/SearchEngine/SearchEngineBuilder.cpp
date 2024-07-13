
#include "SearchEngineBuilder.h"
#include <stdexcept>
#include <sstream>



SearchEngineBuilder &SearchEngineBuilder::Query(const std::string &query) {
    searchEngine_->query = query;
    return *this;
}

SearchEngineBuilder &SearchEngineBuilder::Tags(const std::string &tags) {
    std::stringstream ss(tags);
    std::string t;
    char delimiter = ',';
    while (getline(ss, t, delimiter)) {
        searchEngine_->tags.insert(t);
    }
    return *this;
}

SearchEngine *SearchEngineBuilder::build() {
    if(searchEngine_->query.empty() and searchEngine_->tags.empty()){
        throw std::runtime_error("Query is empty");
    }
    return searchEngine_;
}


