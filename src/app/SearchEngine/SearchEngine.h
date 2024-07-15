#ifndef PROGRA3_SEARCHENGINE_H
#define PROGRA3_SEARCHENGINE_H
#include <string>
#include <unordered_set>
#include <vector>
#include "../Movie/Movie.h"
#include "../TriePrefix/TrieNode.h"


//Builder aplicar aca
class SearchEngine {
    friend class SearchEngineBuilder;
    std::string query;
    std::vector<std::string> tags;
    TrieNode* TitleTree;
    TrieNode* SynopsisTree;
    TrieNode* TagsTree;

public:
    const std::string &getQuery() const;
    const std::vector<std::string> &getTags() const;

    std::vector<Movie*>  execute();
    SearchEngine() = default;
    SearchEngine(TrieNode* pNode, TrieNode* pNode1, TrieNode* pNode2);
    ~SearchEngine() = default;


};

#endif //PROGRA3_SEARCHENGINE_H