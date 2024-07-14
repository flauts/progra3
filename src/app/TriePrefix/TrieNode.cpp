#include "TrieNode.h"
#include "../../tools/Utils.h"

TrieNode::TrieNode() : pool(4) { // Initialize thread pool with 4 threads
    wordEnd = false;
    movieNode = nullptr;
    for (int i = 0; i < 37; i++) {
        childNode[i] = nullptr;
    }
}

void TrieNode::insert_movies_key(const std::vector<std::string>& key, Movie* mov) {
    std::vector<std::future<void>> futures;
    for (const auto& e : key) {
        futures.emplace_back(pool.enqueue([&, e] {
            TrieNode* currentNode = this;
            for (auto c : e) {
                int index;
                if (!isalnum(c)) { continue; }
                if (isdigit(c)) {
                    index = c - '0' + 26;
                } else {
                    index = c - 'a';
                }
                std::lock_guard<std::mutex> lock(nodeMutex);
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
                std::lock_guard<std::mutex> lock(nodeMutex);
                movieNode->vectorPelis.insert(mov);
            }
        }));
    }

    for (auto& future : futures) {
        future.get();
    }
}

unordered_set<Movie*> TrieNode::search_movies_by_key(const std::string& key) {
    TrieNode* currentNode = this;

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

void TrieNode::insert_movies_synopsis(const std::string& key, Movie* mov) {
    std::vector<std::string> words = Utils::splitString(key);
    std::vector<std::future<void>> futures;

    for (const auto& e : words) {
        futures.emplace_back(pool.enqueue([&, e] {
            TrieNode* currentNode = this;
            for (auto c : e) {
                int index;
                if (!isalnum(c)) { continue; }
                if (isdigit(c)) {
                    index = c - '0' + 26;
                } else {
                    c = tolower(c);
                    index = c - 'a';
                }
                std::lock_guard<std::mutex> lock(nodeMutex);
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
                std::lock_guard<std::mutex> lock(nodeMutex);
                movieNode->vectorPelis.insert(mov);
            }
        }));
    }

    for (auto& future : futures) {
        future.get();
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
    for (int i = 0; 37; ++i) {
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