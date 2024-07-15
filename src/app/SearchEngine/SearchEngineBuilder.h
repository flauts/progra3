#ifndef PROGRA3_SEARCHENGINEBUILDER_H
#define PROGRA3_SEARCHENGINEBUILDER_H
#include "SearchEngine.h"

class SearchEngineBuilder {
private:
    int page = 0;
    TrieNode* TitleTree;
    TrieNode* SynopsisTree;
    TrieNode* TagsTree;
    std::string query;
    std::vector<std::string> tags;
    SearchEngine* searchEngine_ = new SearchEngine();
public:
    SearchEngineBuilder& Query(const std::string& query);
    SearchEngineBuilder& Tags(const std::string& tags);
    SearchEngineBuilder& NextPage();
    SearchEngineBuilder& PreviousPage();
    SearchEngineBuilder(TrieNode *pNode, TrieNode *pNode1, TrieNode *pNode2);

    SearchEngine * build();
};

#endif //PROGRA3_SEARCHENGINEBUILDER_H
