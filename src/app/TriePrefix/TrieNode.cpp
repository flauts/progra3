#include "TrieNode.h"
#include "../../tools/Utils.h"



TrieNode::TrieNode() {
    movieNode = nullptr;
    for (auto & i : childNode) {
        i = nullptr;
    }
}

std::vector<std::pair<Movie*,int>>  TrieNode::search_movies_by_key(const std::string& key, TrieNode* currentPastNode) {
    std::vector<std::string> words = Utils::splitString(key);
    std::map<Movie*,int> myMoviesMap;

    for (const auto& word: words) {
        TrieNode* currentNode = this;
        //PARA LOS RECOMENDADOS VECINOS
        if (currentPastNode != nullptr){
            currentNode = currentPastNode;
        }
        for (char c: word) {
            int index;
            if (!isalnum(c)) { continue; }
            if (isdigit(c)) {
                index = c - '0' + 26;
            } else {
                c= tolower(c);
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
                for (auto& mov : movieNode->vectorPelis) {
                    myMoviesMap[mov]++;

                }
            }
        }
    }
    std::vector<std::pair<Movie*,int>> ordered_pairs;
    ordered_pairs.reserve(myMoviesMap.size());
    for (auto& it : myMoviesMap) {
        ordered_pairs.emplace_back(it);
    }
    sort(ordered_pairs.begin(), ordered_pairs.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    return ordered_pairs;
}


void TrieNode::insert_movies_data(const std::string& key, Movie* mov) {
    auto stopwords = Utils::loadStopwords("C:\\Users\\flauta\\progra3\\proyecto\\progra3\\stopwords.txt");
    std::vector<std::string> words = Utils::splitString(key);
    for (auto e: words) {
        e = Utils::cleanString(e);
        TrieNode* currentNode = this;
        if (stopwords.find(e) != stopwords.end()) {
            continue;
        }
        for(auto c: e) {
            int index;
            if (!isalnum(c)) { continue; }
            if (isdigit(c)) {
                index = c - '0' + 26;
            } else{
                c = tolower(c);
                index = c - 'a';
            }
            if (currentNode->childNode[index] == nullptr) {
                currentNode->childNode[index] = new TrieNode();
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

TrieNodeVector::TrieNodeVector(const std::unordered_set<Movie *> &vectorPelis) : vectorPelis(vectorPelis) {}
//
//void TrieNode::serialize(std::ofstream& out) const {
//    // Write wordEnd
//    out.write(reinterpret_cast<const char*>(&wordEnd), sizeof(bool));
//
//    // Write if movieNode exists
//    bool hasMovieNode = (movieNode != nullptr);
//    out.write(reinterpret_cast<const char*>(&hasMovieNode), sizeof(bool));
//
//    if (hasMovieNode) {
//        TrieNodeVector* movieNodeVector = dynamic_cast<TrieNodeVector*>(movieNode);
//        if (movieNodeVector) {
//            size_t movieCount = movieNodeVector->vectorPelis.size();
//            out.write(reinterpret_cast<const char*>(&movieCount), sizeof(size_t));
//
//            // Here you would serialize each Movie* in vectorPelis
//            // For this example, we'll just write the pointer addresses
//            for (const Movie* movie : movieNodeVector->vectorPelis) {
//                out.write(reinterpret_cast<const char*>(&movie), sizeof(Movie*));
//            }
//        }
//    }
//
//    // Write child nodes
//    for (int i = 0; i < 37; ++i) {
//        bool hasChild = (childNode[i] != nullptr);
//        out.write(reinterpret_cast<const char*>(&hasChild), sizeof(bool));
//        if (hasChild) {
//            childNode[i]->serialize(out);
//        }
//    }
//}
//
//
//TrieNode* TrieNode::deserialize(std::ifstream& in) {
//    TrieNode* node = new TrieNode();
//
//    // Read wordEnd
//    in.read(reinterpret_cast<char*>(&node->wordEnd), sizeof(bool));
//
//    // Read if movieNode exists
//    bool hasMovieNode;
//    in.read(reinterpret_cast<char*>(&hasMovieNode), sizeof(bool));
//
//    // If movieNode exists, deserialize TrieNodeVector
//    if (hasMovieNode) {
//        TrieNodeVector* movieNodeVector = new TrieNodeVector();
//        size_t movieCount;
//        in.read(reinterpret_cast<char*>(&movieCount), sizeof(size_t));
//
//        // Here you would deserialize each Movie* in vectorPelis
//        // For this example, we're just reading the pointer addresses
//        for (size_t i = 0; i < movieCount; ++i) {
//            Movie* movie;
//            in.read(reinterpret_cast<char*>(&movie), sizeof(Movie*));
//            movieNodeVector->vectorPelis.insert(movie);
//        }
//
//        node->movieNode = movieNodeVector;
//    }
//
//    // Read child nodes
//    for (int i = 0; i < 37; ++i) {
//        bool hasChild;
//        in.read(reinterpret_cast<char*>(&hasChild), sizeof(bool));
//        if (hasChild) {
//            node->childNode[i] = deserialize(in);
//        } else {
//            node->childNode[i] = nullptr;
//        }
//    }
//    return node;
//}