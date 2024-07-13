//
// Created by jorughen on 7/13/24.
//

#include "TrieNode.h"

TrieNode::TrieNode() {
    // constructor
    // initialize the wordEnd variable with false
    // initialize every index of childNode array with
    // NULL
    wordEnd = false;

    for (int i = 0; i < 26; i++) {
        childNode[i] = nullptr;
    }
}

void insert_key(TrieNode* root, string& key)
{
    // Initialize the currentNode pointer
    // with the root node
    TrieNode* currentNode = root;

    // Iterate across the length of the string
    for (int i = 0; i < key.length(); i++){
        char c = key[i];
        // Check if the node exist for the current
        // character in the Trie.
        if (isdigit(c)){
            c -= '0'+27;
        }
        else{
            c -= 'a';
        }

        if (currentNode->childNode[c] == nullptr) {

            // If node for current character does not exist
            // then make a new node
            TrieNode* newNode = new TrieNode();

            // Keep the reference for the newly created
            // node.
            currentNode->childNode[c] = newNode;
        }
        // Now, move the current node pointer to the newly
        // created node.
        currentNode = currentNode->childNode[c];
    }

    // Increment the wordEndCount for the last currentNode
    // pointer this implies that there is a string ending at
    // currentNode.
    currentNode->wordEnd = true;


<<<<<<< HEAD:src/app/TriePrefix/TriePrefix.cpp
=======

>>>>>>> 70d202b473c650195556eb692756d0cd2f192e6b:src/app/TriePrefix/TrieNode.cpp
}

bool search_key(TrieNode* root, string& key)
{
    // Initialize the currentNode pointer
    // with the root node
    TrieNode* currentNode = root;

    // Iterate across the length of the string
    for (auto c : key) {

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->childNode[c - 'a'] == nullptr) {

            // Given word does not exist in Trie
            return false;
        }

        // Move the currentNode pointer to the already
        // existing node for current character.
        currentNode = currentNode->childNode[c - 'a'];
    }

    return currentNode->wordEnd;
}

