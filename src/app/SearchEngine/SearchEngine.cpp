#include "SearchEngine.h"

const std::string &SearchEngine::getQuery() const {
    return query;
}

const std::vector<std::string> &SearchEngine::getTags() const {
    return tags;
}

SearchEngine::SearchEngine(TrieNode *pNode, TrieNode *pNode1, TrieNode *pNode2) {
    this->TitleTree = pNode;
    this->SynopsisTree = pNode1;
    this->TagsTree = pNode2;

}

std::map<Movie*, int> mergeMaps(const std::map<Movie*, int>& map1, const std::map<Movie*, int>& map2, const std::map<Movie*, int>& map3) {
    std::map<Movie*, int> result = map1;

    if(map1.empty()){
        return result;
    }
    for (const auto& pair : map2) {
        result[pair.first] += pair.second;
    }

    for (const auto& pair : map3) {
        result[pair.first] += pair.second;
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

std::vector<Movie*> SearchEngine::execute() {
    auto set1 = TitleTree->search_movies_by_title(query);
    auto set2 = SynopsisTree->search_movies_by_synopsy(query);
    auto set3 = TagsTree->search_movies_by_tag(tags);

    return mergeAndSort(set1, set2, set3);
}