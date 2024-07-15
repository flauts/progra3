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

class TrieNodeVector;

struct TrieNode {
    TrieNode* childNode[37]{};
    TrieNode* movieNode;
    std::mutex mtx;

    TrieNode();
    virtual ~TrieNode() = default;

    void insert_movies_data(const std::string &key, Movie *mov);

    void insert_movies_title(const std::string &key, Movie *mov);

    std::map<Movie *, int> search_movies_by_title(const std::string& key);

    std::map<Movie *, int> search_movies_by_synopsy(const std::string &key);

    void search_word(const std::string &word, std::map<Movie *, int> &myMoviesMap, int weight);

    std::map<Movie *, int> search_movies_by_tag(const std::vector<std::string> &tags);
};

struct TrieNodeVector : public TrieNode {
    std::unordered_set<Movie*> vectorPelis = std::unordered_set<Movie*>();
    TrieNodeVector() = default;

    explicit TrieNodeVector(const std::unordered_set<Movie *> &vectorPelis);
};

#endif // PROGRA3_TRIENODE_H