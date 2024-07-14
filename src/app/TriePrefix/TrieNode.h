#ifndef PROGRA3_TRIENODE_H
#define PROGRA3_TRIENODE_H

#include <bits/stdc++.h>
#include "../Movie/Movie.h"
using namespace std;

struct TrieNode {
    TrieNode* childNode[37]; // 26 letters + 10 digits + 1 special node
    bool wordEnd;
    TrieNode* movieNode; // Puntero a TrieNodeVector

    TrieNode();
    virtual ~TrieNode() = default; // Destructor virtual

    void insert_movies_key(const std::vector<std::string>& key, Movie* mov); // Modificación aquí
    unordered_set<Movie*> search_movies_by_key(const std::string& key); // También modificamos aquí
};

struct TrieNodeVector : public TrieNode {
    unordered_set<Movie*> vectorPelis = unordered_set<Movie*>();
    TrieNodeVector() = default;
};


#endif // PROGRA3_TRIENODE_H