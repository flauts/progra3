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
};

struct TrieNodeVector : public TrieNode {
    vector<Movie*> vectorPelis;

    TrieNodeVector() : TrieNode() {
        vectorPelis = vector<Movie*>();
    }
};

void insert_key(TrieNode* root, const std::string& key, Movie* mov); // Modificación aquí
vector<Movie*> search_key(TrieNode* root, const std::string& key); // También modificamos aquí

#endif // PROGRA3_TRIENODE_H

