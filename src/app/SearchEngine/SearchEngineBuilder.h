#ifndef PROGRA3_SEARCHENGINEBUILDER_H
#define PROGRA3_SEARCHENGINEBUILDER_H
#include "SearchEngine.h"

class SearchEngineBuilder {
private:
    TrieNode* TitleTree;
    TrieNode* SynopsisTree;
    TrieNode* TagsTree;
    SearchEngine* searchEngine_ = new SearchEngine(TitleTree, SynopsisTree, TagsTree);
public:
    SearchEngineBuilder& Query(const std::string& query);
    SearchEngineBuilder& Tags(const std::string& tags);
    SearchEngine* build();

    SearchEngineBuilder(TrieNode *pNode, TrieNode *pNode1, TrieNode *pNode2);
};

#endif //PROGRA3_SEARCHENGINEBUILDER_H
