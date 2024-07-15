#include "SearchEngineBuilder.h"
#include <stdexcept>
#include <sstream>
#include "../../tools/Utils.h"

namespace fs = std::filesystem;

SearchEngineBuilder &SearchEngineBuilder::Query(const std::string &query) {
    this->query = query;
    return *this;
}

SearchEngineBuilder &SearchEngineBuilder::Tags(const std::string &tags) {
    this->tags = Utils::splitString(tags);
    return *this;
}

SearchEngineBuilder::SearchEngineBuilder(TrieNode *pNode, TrieNode *pNode1, TrieNode *pNode2) {
    this->TitleTree = pNode;
    this->SynopsisTree = pNode1;
    this->TagsTree = pNode2;
}

std::map<Movie*, int> mergeMaps(const std::map<Movie*, int>& map1, const std::map<Movie*, int>& map2, const std::map<Movie*, int>& map3) {
    std::map<Movie*, int> result;
    if(!map1.empty()){
        result = map1;
        for (const auto& pair : map2) {
            result[pair.first] += pair.second;
        }

        for (const auto& pair : map3) {
            result[pair.first] += pair.second;
        }
    }else{
        result = map3;
    }

    return result;
}

std::vector<Movie*> sortMapByValueDescending(const std::map<Movie*, int>& map) {
    std::vector<std::pair<Movie*, int>> vec(map.begin(), map.end());

    std::sort(vec.begin(), vec.end(), [](const std::pair<Movie*, int>& a, const std::pair<Movie*, int>& b) {
        return b.second < a.second;
    });

    std::vector<Movie*> sortedKeys;
    for (const auto& pair : vec) {
        sortedKeys.push_back(pair.first);
    }

    return sortedKeys;
}

std::vector<Movie*> mergeAndSort(const std::map<Movie*, int>& map1, const std::map<Movie*, int>& map2, const std::map<Movie*, int>& map3) {
    std::map<Movie*, int> mergedMap = mergeMaps(map1, map2, map3);
    return sortMapByValueDescending(mergedMap);
}

SearchEngine* SearchEngineBuilder::build() {
    if(this->query.empty() and this->tags.empty()){
        throw std::runtime_error("Query and tag is empty");
    }
    auto set1 = TitleTree->search_movies_by_title(query);
    auto set2 = SynopsisTree->search_movies_by_synopsy(query);
    auto set3 = TagsTree->search_movies_by_tag(tags);

    movies = mergeAndSort(set1, set2, set3);
    std::copy_n(movies.begin(), 5, searchEngine_->movies.begin());
    return searchEngine_;
}

SearchEngine* SearchEngineBuilder::getNextPage() {
    ++page;
    for (int i = page*5; i < page*5+5; ++i) {
        searchEngine_->movies[i] = movies[i];
    }

    return searchEngine_;
}

SearchEngine* SearchEngineBuilder::getBeforePage() {
    --page;
    for (int i = page*5; i < page*5+5; ++i) {
        searchEngine_->movies[i] = movies[i];
    }

    return searchEngine_;
}

