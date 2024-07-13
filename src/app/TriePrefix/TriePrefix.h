//
// Created by jorughen on 7/13/24.
//

#ifndef PROGRA3_TRIEPREFIX_H
#define PROGRA3_TRIEPREFIX_H

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {

    // pointer array for child nodes of each node
    TrieNode* childNode[26];

    // Used for indicating ending of string
    bool wordEnd;

    TrieNode();

};

void insert_key(TrieNode* root, string& key);
bool search_key(TrieNode* root, string& key);

#endif //PROGRA3_TRIEPREFIX_H
