#ifndef PROGRA3_SEARCHENGINE_H
#define PROGRA3_SEARCHENGINE_H
#include <string>
#include <unordered_set>
#include <vector>

//Builder aplicar aca
class SearchEngine {
    friend class SearchEngineBuilder;
    std::string query;
    std::vector<std::string> tags;
};

#endif //PROGRA3_SEARCHENGINE_H
