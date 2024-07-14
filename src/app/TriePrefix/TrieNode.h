#ifndef PROGRA3_TRIENODE_H
#define PROGRA3_TRIENODE_H

#include <bits/stdc++.h>
#include "../Movie/Movie.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>

class TrieNodeVector;

struct TrieNode {
    TrieNode* childNode[37];
    bool wordEnd;
    TrieNode* movieNode;

    TrieNode();
    virtual ~TrieNode() = default;

    std::vector<std::pair<Movie*,int>> search_movies_by_key(const std::string& key, TrieNode* currentPastNode = nullptr);
    void insert_movies_data(const std::string &key, Movie *mov);

    // Serialization method
    void serialize(std::ofstream& out) const;

    // Deserialization method
    static TrieNode* deserialize(std::ifstream& in);
};

struct TrieNodeVector : public TrieNode {
    std::unordered_set<Movie*> vectorPelis = std::unordered_set<Movie*>();
    TrieNodeVector() = default;

    explicit TrieNodeVector(const std::unordered_set<Movie *> &vectorPelis);
};


#endif // PROGRA3_TRIENODE_H