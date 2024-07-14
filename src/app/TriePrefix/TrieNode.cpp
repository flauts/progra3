#include "TrieNode.h"

TrieNode::TrieNode() {
    wordEnd = false;
    for (int i = 0; i < 26; i++) {
        childNode[i] = nullptr;
    }
}

void TrieNode::setMovies(const vector<Movie *> &movies) {
    TrieNode::movies = movies;
}

void TrieNode::insert_key(string& key)
{
    TrieNode* currentNode = this;

    // Iterate across the length of the string
    for (int i = 0; i < key.length(); i++){
        char c = key[i];
        if (isdigit(c)){
            c = c - '0' + 27;
        }
        else{
            c = c - 'a';
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
}

bool TrieNode::search_key(string& key)
{
    // Initialize the currentNode pointer
    // with the root node
    TrieNode* currentNode = this;

    // Iterate across the length of the string
    for (auto c : key){
        if (isdigit(c)){
            c -= '0'+27;
        }
        else{
            c -= 'a';
        }

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->childNode[c] == nullptr) {

            // Given word does not exist in Trie
            return false;
        }

        // Move the currentNode pointer to the already
        // existing node for current character.
        currentNode = currentNode->childNode[c];
    }

    return currentNode->wordEnd;
}

