#ifndef PROGRA3_TRIENODE_H
#define PROGRA3_TRIENODE_H

#include <bits/stdc++.h>
#include "../Movie/Movie.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <mutex>
#include <thread>
#include "ThreadPool.h"

class TrieNodeVector;

struct TrieNode {
    TrieNode* childNode[37];
    bool wordEnd;
    TrieNode* movieNode;
    std::mutex nodeMutex;
    ThreadPool pool;

    TrieNode();
    virtual ~TrieNode() = default;

    std::unordered_set<Movie*> search_movies_by_key(const std::string& key);
    void insert_movies_key(const std::vector<std::string>& key, Movie* mov);
    void insert_movies_synopsis(const std::string& key, Movie* mov);

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
