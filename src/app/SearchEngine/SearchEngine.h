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

public:
    const std::string &getQuery() const;
    const std::vector<std::string> &getTags() const;
    const std::vector<Movie*> execute();
    ~SearchEngine() = default;

};

#endif //PROGRA3_SEARCHENGINE_H