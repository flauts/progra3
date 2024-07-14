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

std::unordered_set<Movie*> TrieNode::search_movies_by_key(const std::string& key) {
    std::vector<std::string> words = Utils::splitString(key);
    std::vector<std::unordered_set<Movie*>> results(words.size());

    if (words.empty()) {
        return {};
    }

#pragma omp parallel for
    for (int i = 0; i < words.size(); ++i) {
        TrieNode* currentNode = this;
        for (char c : words[i]) {
            if (!isalnum(c)) { continue; }
            int index;
            if (isdigit(c)) {
                index = c - '0' + 26;
            } else {
                c = tolower(c);
                index = c - 'a';
            }

            if (currentNode->childNode[index] == nullptr) {
                break;
            }

            currentNode = currentNode->childNode[index];
        }

        if (currentNode->childNode[36] != nullptr) {
            TrieNodeVector* movieNode = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
            if (movieNode) {
                results[i] = movieNode->vectorPelis;
            }
        }
    }

    // Compute intersection
    std::unordered_set<Movie*> finalResult = results[0];
    for (int i = 1; i < results.size(); ++i) {
        std::unordered_set<Movie*> intersection;
        for (auto& mov : finalResult) {
            if (results[i].find(mov) != results[i].end()) {
                intersection.insert(mov);
            }
        }
        finalResult = intersection;
    }

    return finalResult;
}

void TrieNode::insert_movies_data(const std::string& key, Movie* mov) {
    std::vector<std::string> words = Utils::splitString(key);
#pragma omp parallel for
    for (int i = 0; i < words.size(); ++i) {
        TrieNode* currentNode = this;
        for (char c : words[i]) {
            int index;
            if (!isalnum(c)) { continue; }
            if (isdigit(c)) {
                index = c - '0' + 26;
            } else {
                c = tolower(c);
                index = c - 'a';
            }

            TrieNode* nextNode;
#pragma omp critical
            {
                if (currentNode->childNode[index] == nullptr) {
                    currentNode->childNode[index] = new TrieNode();
                }
                nextNode = currentNode->childNode[index];
            }
            currentNode = nextNode;
        }

#pragma omp critical
        {
            if (currentNode->childNode[36] == nullptr) {
                currentNode->childNode[36] = new TrieNodeVector();
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