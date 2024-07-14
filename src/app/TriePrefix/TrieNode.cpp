#include "TrieNode.h"
#include "../../tools/Utils.h"


TrieNode::TrieNode() {
    wordEnd = false;
    movieNode = nullptr;
    for (int i = 0; i < 37; i++) {
        childNode[i] = nullptr;
    }
}


//cada tag es todo junto sin espacios
//paralelismo con el insert


void TrieNode::insert_movies_key(const std::vector<std::string>& key, Movie* mov) { // Modificación aquí
    TrieNode* currentNode = this;
    for(auto e: key) {
        for (auto c: e) {
            int index;
            if(!isalnum(c)){continue;}
            if (isdigit(c)) {
                index = c - '0' + 26;
            } else {
                index = c - 'a';
            }
            if (currentNode->childNode[index] == nullptr) {
                TrieNode *newNode = new TrieNode();
                currentNode->childNode[index] = newNode;
            }
            currentNode = currentNode->childNode[index];
        }

        if (currentNode->childNode[36] == nullptr) {
            TrieNodeVector *newNode = new TrieNodeVector();
            currentNode->childNode[36] = newNode;
        }

        TrieNodeVector* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
        if (movieNode) {
            movieNode->vectorPelis.insert(mov);
        }
    }


}


unordered_set<Movie*> TrieNode::search_movies_by_key(const string& key) {
    vector<string> words = Utils::splitString(key);
    unordered_set<Movie*> result;

    if (words.empty()) {
        return result; // Si no hay palabras, devuelve un conjunto vacío
    }

    bool firstWord = true;

    for (const auto& e : words) {
        TrieNode* currentNode = this;
        unordered_set<Movie*> currentMovies;

        for (char c : e) {
            if (!isalnum(c)) { continue; }
            int index;
            if (isdigit(c)) {
                index = c - '0' + 26;
            } else {
                c = tolower(c);
                index = c - 'a';
            }

            if (currentNode->childNode[index] == nullptr) {
                return {}; // Devuelve un conjunto vacío si una de las palabras no existe
            }

            currentNode = currentNode->childNode[index];
        }

        if (currentNode->childNode[36] != nullptr) {
            TrieNodeVector* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
            if (movieNode) {
                for (auto mov : movieNode->vectorPelis) {
                    currentMovies.insert(mov);
                }
            }
        }

        if (firstWord) {
            result = currentMovies;
            firstWord = false;
        } else {
            // Intersección de conjuntos
            unordered_set<Movie*> intersection;
            for (auto& mov : result) {
                if (currentMovies.find(mov) != currentMovies.end()) {
                    intersection.insert(mov);
                }
            }
            result = intersection;

            if (result.empty()) {
                return result; // Si la intersección es vacía, no hay películas que coincidan con todas las palabras
            }
        }
    }

    return result; // Devuelve el conjunto de películas que coinciden con todas las palabras
}



void TrieNode::insert_movies_synopsis(const std::string& key, Movie* mov) {
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
                    TrieNode *newNode = new TrieNode();
                    currentNode->childNode[index] = newNode;
                }
                currentNode = currentNode->childNode[index];
            }
            if (currentNode->childNode[36] == nullptr) {
                TrieNodeVector *newNode = new TrieNodeVector();
                currentNode->childNode[36] = newNode;
            }
            TrieNodeVector* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
            if (movieNode) {
                movieNode->vectorPelis.insert(mov);
            }
        }
    }