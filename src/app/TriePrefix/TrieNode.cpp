#include "TrieNode.h"
#include "../../tools/Utils.h"
namespace fs = std::filesystem;

void TrieNode::search_word(const std::string& word, std::map<Movie*, int>& myMoviesMap, int weight) {
    TrieNode* currentNode = this;
    for (char c : word) {
        int index;
        if (!isalnum(c)) { continue; }
        if (isdigit(c)) {
            index = c - '0' + 26;
        } else {
            c = tolower(c);
            index = c - 'a';
        }
        if (currentNode->childNode[index] == nullptr) {
            return;
        }
        currentNode = currentNode->childNode[index];
    }

    if (currentNode->childNode[36] != nullptr) {
        auto* nodeMovie = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
        if (nodeMovie) {
            std::lock_guard<std::mutex> lock(mtx);
            for (auto& mov : nodeMovie->vectorPelis) {
                myMoviesMap[mov] += weight;
            }
        }
    }
}

std::map<Movie*, int> TrieNode::search_movies_by_tag(const std::vector<std::string>& tags) {
    std::map<Movie*, int> myMoviesMap;
    std::vector<std::thread> threads;

    for (const auto& word : tags) {
        threads.emplace_back(&TrieNode::search_word, this, word, std::ref(myMoviesMap), 100);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return myMoviesMap;
}

std::map<Movie*, int> TrieNode::search_movies_by_title(const std::string& key) {
    std::vector<std::string> words = Utils::splitString(key);
    std::map<Movie*, int> myMoviesMap;
    std::vector<std::thread> threads;

    for (const auto& word : words) {
        threads.emplace_back(&TrieNode::search_word, this, word, std::ref(myMoviesMap), 1000);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return myMoviesMap;
}

std::map<Movie*, int> TrieNode::search_movies_by_synopsy(const std::string& key) {
    fs::path projectDir = fs::absolute(fs::path(__FILE__).parent_path().parent_path().parent_path().parent_path());
    auto stopwords = Utils::loadStopwords(projectDir.string() + "stopwords.txt");
    std::vector<std::string> words = Utils::splitString(key);
    std::map<Movie*, int> myMoviesMap;
    std::vector<std::thread> threads;

    for (const auto& word : words) {
        if (stopwords.find(word) != stopwords.end()) {
            continue;
        }
        threads.emplace_back(&TrieNode::search_word, this, word, std::ref(myMoviesMap), 1);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return myMoviesMap;
}



TrieNode::TrieNode() {
    movieNode = nullptr;
    for (auto & i : childNode) {
        i = nullptr;
    }
}


void TrieNode::insert_movies_data(const std::string& key, Movie* mov) {
    fs::path projectDir = fs::absolute(fs::path(__FILE__).parent_path().parent_path().parent_path().parent_path());
    auto stopwords = Utils::loadStopwords(projectDir.string()+"/stopwords.txt");
    std::vector<std::string> words = Utils::splitString(key);
    TrieNode* currentNode;
    for (auto e: words) {
        e = Utils::to_ascii(e);
        currentNode = this;
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
        auto* nodeMovie = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
        if (nodeMovie) {
            nodeMovie->vectorPelis.insert(mov);
        }
    }
}

void TrieNode::insert_movies_title(const std::string& key, Movie* mov) {
    std::vector<std::string> words = Utils::splitString(key);
    TrieNode* currentNode;
    for (auto e: words) {
        e = Utils::to_ascii(e);
         currentNode = this;
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
        auto* nodeMovie = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
        if (nodeMovie) {
            nodeMovie->vectorPelis.insert(mov);
        }
    }
}


TrieNodeVector::TrieNodeVector(const std::unordered_set<Movie *> &vectorPelis) : vectorPelis(vectorPelis) {}
