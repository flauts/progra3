#include "TrieNode.h"

TrieNode::TrieNode() {
    wordEnd = false;
    movieNode = nullptr;
    for (int i = 0; i < 37; i++) {
        childNode[i] = nullptr;
    }
}

void insert_key(TrieNode* root, const std::string& key, Movie* mov) { // Modificación aquí
    TrieNode* currentNode = root;

    for (int i = 0; i < key.length(); i++) {
        char c = key[i];
        int index;
        if (isdigit(c)) {
            index = c - '0' + 26;
        } else {
            index = c - 'a';
        }

        if (currentNode->childNode[index] == nullptr) {
            TrieNode* newNode = new TrieNode();
            currentNode->childNode[index] = newNode;
        }

        currentNode = currentNode->childNode[index];
    }

    if (currentNode->childNode[36] == nullptr) {
        TrieNodeVector* newNode = new TrieNodeVector();
        currentNode->childNode[36] = newNode;
    }

    TrieNodeVector* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
    if (movieNode) {
        movieNode->vectorPelis.push_back(mov);
    }
}

vector<Movie*> search_key(TrieNode* root, const std::string& key) { // Modificación aquí
    TrieNode* currentNode = root;

    for (auto c : key) {
        int index;
        if (isdigit(c)) {
            index = c - '0' + 26;
        } else {
            index = c - 'a';
        }

        if (currentNode->childNode[index] == nullptr) {
            return {}; // Devuelve un vector vacío si la clave no existe
        }

        currentNode = currentNode->childNode[index];
    }

    if (currentNode->childNode[36] != nullptr) {
        TrieNodeVector* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
        if (movieNode) {
            return movieNode->vectorPelis;
        }
    }

    return {}; // Devuelve un vector vacío si no hay películas asociadas con la clave
}
