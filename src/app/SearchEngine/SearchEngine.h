#ifndef PROGRA3_SEARCHENGINE_H
#define PROGRA3_SEARCHENGINE_H
#include <string>
#include <unordered_set>
#include <vector>
#include "../Movie/Movie.h"
#include "../TriePrefix/TrieNode.h"
#include <array>

//Builder aplicar aca
class SearchEngine {
    friend class SearchEngineBuilder;
    std::array<Movie*,5> movies;
public:
    std::array<Movie*,5> get();
    SearchEngine() = default;
    ~SearchEngine() = default;


};

#endif //PROGRA3_SEARCHENGINE_H