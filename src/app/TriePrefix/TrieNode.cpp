#include <omp.h>
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


std::unordered_set<Movie*> TrieNode::search_movies_by_key(const std::string& key) {
    std::vector<std::string> words = Utils::splitString(key);
    std::unordered_set<Movie*> result;

    if (words.empty()) {
        return result; // Si no hay palabras, devuelve un conjunto vacío
    }

    bool firstWord = true;

    for (const auto& e : words) {
        TrieNode* currentNode = this;
        std::unordered_set<Movie*> currentMovies;

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
            std::unordered_set<Movie*> intersection;
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

void TrieNode::insert_movies_data(const std::string& key, Movie* mov) {
    omp_set_num_threads(4);
    TrieNode* currentNode = this;
    std::vector<std::string> words = Utils::splitString(key);
    #pragma omp parallel for
    {
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
}

TrieNodeVector::TrieNodeVector(const std::unordered_set<Movie *> &vectorPelis) : vectorPelis(vectorPelis) {}

void TrieNode::serialize(std::ofstream& out) const {
    // Write wordEnd
    out.write(reinterpret_cast<const char*>(&wordEnd), sizeof(bool));

    // Write if movieNode exists
    bool hasMovieNode = (movieNode != nullptr);
    out.write(reinterpret_cast<const char*>(&hasMovieNode), sizeof(bool));

    // If movieNode exists, serialize TrieNodeVector
    if (hasMovieNode) {
        TrieNodeVector* movieNodeVector = dynamic_cast<TrieNodeVector*>(movieNode);
        if (movieNodeVector) {
            size_t movieCount = movieNodeVector->vectorPelis.size();
            out.write(reinterpret_cast<const char*>(&movieCount), sizeof(size_t));

            // Here you would serialize each Movie* in vectorPelis
            // For this example, we'll just write the pointer addresses
            for (const Movie* movie : movieNodeVector->vectorPelis) {
                out.write(reinterpret_cast<const char*>(&movie), sizeof(Movie*));
            }
        }
    }

    // Write child nodes
    for (int i = 0; i < 37; ++i) {
        bool hasChild = (childNode[i] != nullptr);
        out.write(reinterpret_cast<const char*>(&hasChild), sizeof(bool));
        if (hasChild) {
            childNode[i]->serialize(out);
        }
    }
}

TrieNode* TrieNode::deserialize(std::ifstream& in) {
    TrieNode* node = new TrieNode();

    // Read wordEnd
    in.read(reinterpret_cast<char*>(&node->wordEnd), sizeof(bool));

    // Read if movieNode exists
    bool hasMovieNode;
    in.read(reinterpret_cast<char*>(&hasMovieNode), sizeof(bool));

    // If movieNode exists, deserialize TrieNodeVector
    if (hasMovieNode) {
        TrieNodeVector* movieNodeVector = new TrieNodeVector();
        size_t movieCount;
        in.read(reinterpret_cast<char*>(&movieCount), sizeof(size_t));

        // Here you would deserialize each Movie* in vectorPelis
        // For this example, we're just reading the pointer addresses
        for (size_t i = 0; i < movieCount; ++i) {
            Movie* movie;
            in.read(reinterpret_cast<char*>(&movie), sizeof(Movie*));
            movieNodeVector->vectorPelis.insert(movie);
        }

        node->movieNode = movieNodeVector;
    }

    // Read child nodes
    for (int i = 0; i < 37; ++i) {
        bool hasChild;
        in.read(reinterpret_cast<char*>(&hasChild), sizeof(bool));
        if (hasChild) {
            node->childNode[i] = deserialize(in);
        } else {
            node->childNode[i] = nullptr;
        }
    }

    return node;
}