#ifndef PROGRA3_SEARCHENGINEBUILDER_H
#define PROGRA3_SEARCHENGINEBUILDER_H
#include "SearchEngine.h"

class SearchEngineBuilder {
private:
    SearchEngine* searchEngine_ = new SearchEngine();
public:
    SearchEngineBuilder& Query(const std::string& query);
    SearchEngineBuilder& Tags(const std::string& tags);
    SearchEngine* build();

};

#endif //PROGRA3_SEARCHENGINEBUILDER_H
