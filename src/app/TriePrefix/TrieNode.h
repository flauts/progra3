//
// Created by jorughen on 7/13/24.
//

#ifndef PROGRA3_TRIENODE_H
#define PROGRA3_TRIENODE_H

#include <bits/stdc++.h>
#include "../Movie/Movie.h"

using namespace std;

struct TrieNode{
    // pointer array for child nodes of each node
    TrieNode* childNode[36];
    // Used for indicating ending of string
    bool wordEnd = false;
    //pointer
    vector<Movie*> movies;
    // Constructor
    TrieNode();
public:
    void setMovies(const vector<Movie *> &movies);
    void insert_key(string& key);
    bool search_key(string& key);
};
#endif //PROGRA3_TRIENODE_H
