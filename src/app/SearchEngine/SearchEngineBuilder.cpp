#include "SearchEngineBuilder.h"
#include <stdexcept>
#include <sstream>
#include "../../tools/Utils.h"

namespace fs = std::filesystem;

SearchEngineBuilder &SearchEngineBuilder::Query(const std::string &query) {
    if(!searchEngine_->getQuery().contains(query)){
        searchEngine_->query="";
    }
    searchEngine_->query += query;
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
        throw std::runtime_error("Query is empty");
    }
    return searchEngine_;
}

SearchEngineBuilder::SearchEngineBuilder(TrieNode *pNode, TrieNode *pNode1, TrieNode *pNode2) {
    searchEngine_->TitleTree = pNode;
    searchEngine_->SynopsisTree = pNode1;
    searchEngine_->TagsTree = pNode2;
}
