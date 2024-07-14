#include "TrieNode.h"
#include "../../tools/Utils.h"


TrieNode::TrieNode() {
    wordEnd = false;
    movieNode = nullptr;
    for (auto & i : childNode) {
        i = nullptr;
    }
}

//cada tag es todo junto sin espacios
//paralelismo con el insert

//
//void TrieNode::insert_movies_tag(const std::vector<std::string>& key, Movie* mov) { // Modificación aquí
//    TrieNode* currentNode = this;
//    for(auto e: key) {
//        for (auto c: e) {
//            int index;
//            if(!isalnum(c)){continue;}
//            if (isdigit(c)) {
//                index = c - '0' + 26;
//            } else {
//                index = c - 'a';
//            }
//            if (currentNode->childNode[index] == nullptr) {
//                TrieNode *newNode = new TrieNode();
//                currentNode->childNode[index] = newNode;
//            }
//            currentNode = currentNode->childNode[index];
//        }
//
//        if (currentNode->childNode[36] == nullptr) {
//            TrieNodeVector *newNode = new TrieNodeVector();
//            currentNode->childNode[36] = newNode;
//        }
//
//        TrieNodeVector* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
//        if (movieNode) {
//            movieNode->vectorPelis.insert(mov);
//        }
//    }
//
//}


unordered_set<Movie*>TrieNode::search_movies_by_key(const std::string& key) { // Modificación aquí
    TrieNode* currentNode = this;
    vector<string> words = Utils::splitString(key);
    unordered_set<Movie*> movies;
    for (const auto& e: words) {
        currentNode=this;
        for (auto c: e) {
            int index;
            if (!isalnum(c)) { continue; }
            if (isdigit(c)) {
                index = c - '0' + 26;
            } else {
                c = tolower(c);
                index = c - 'a';
            }

            if (currentNode->childNode[index] == nullptr) {
                return {}; // Devuelve un vector vacío si la clave no existe
            }

            currentNode = currentNode->childNode[index];
        }

        if (currentNode->childNode[36] != nullptr) {
            TrieNodeVector *movieNode = dynamic_cast<TrieNodeVector *>(currentNode->childNode[36]);
            if (movieNode) {
                for (auto mov : movieNode->vectorPelis) {
                    movies.insert(mov);
                }
            }
        }
    }

    return movies; // Devuelve un vector vacío si no hay películas asociadas con la clave
}

void TrieNode::insert_movies_data(const std::string& key, Movie* mov) {
    TrieNode* currentNode = this;
        vector<string> words = Utils::splitString(key);
            for (auto e: words) {
                currentNode=this;
                for(auto c: e) {
                int index;
                if (!isalnum(c)) { continue; }
                if (isdigit(c)) {
                    index = c - '0' + 26;
                } else {
                    c = tolower(c);
                    index = c - 'a';
                }
                if (currentNode->childNode[index] == nullptr) {
                    auto *newNode = new TrieNode();
                    currentNode->childNode[index] = newNode;
                }
                currentNode = currentNode->childNode[index];
            }
            if (currentNode->childNode[36] == nullptr) {
                auto *newNode = new TrieNodeVector();
                currentNode->childNode[36] = newNode;
            }
            auto* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
            if (movieNode) {
                movieNode->vectorPelis.insert(mov);
            }
        }
    }