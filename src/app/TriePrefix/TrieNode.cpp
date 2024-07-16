
#include "TrieNode.h"
#include "../../tools/Utils.h"

namespace fs = std::filesystem;



TrieNode::TrieNode() {
    movieNode = nullptr;
    for (auto & i : childNode) {
        i = nullptr;
    }
}


std::map<Movie*,int>  TrieNode::search_movies_by_tag(const std::vector<std::string>& tags) {
    std::map<Movie*,int> myMoviesMap;
    for (const auto& word: tags) {
        TrieNode* currentNode = this;
        //PARA LOS RECOMENDADOS VECINOS
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
            auto* nodeMovie = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
            if (nodeMovie) {
                for (auto& mov : nodeMovie->vectorPelis) {
                    myMoviesMap[mov]+=100;

                }
            }
        }
    }

    return myMoviesMap;
}


std::map<Movie*,int>  TrieNode::search_movies_by_title(const std::string& key) {
    std::vector<std::string> words = Utils::splitString(key);
    std::map<Movie*,int> myMoviesMap;

    for (const auto& word: words) {
        TrieNode* currentNode = this;
        //PARA LOS RECOMENDADOS VECINOS

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
            auto* nodeMovie = dynamic_cast<TrieNodeVector*>(currentNode->childNode[36]);
            if (nodeMovie) {
                for (auto& mov : nodeMovie->vectorPelis) {
                    myMoviesMap[mov]+=1000;

                }
            }
        }
    }

    return myMoviesMap;
}

std::map<Movie*,int>  TrieNode::search_movies_by_synopsy(const std::string& key) {
    fs::path projectDir = fs::absolute(fs::path(__FILE__).parent_path().parent_path().parent_path().parent_path());
    auto stopwords = Utils::loadStopwords(projectDir.string() + "stopwords.txt");
    std::vector<std::string> words = Utils::splitString(key);
    std::map<Movie *, int> myMoviesMap;

    for (const auto &word: words) {
        TrieNode *currentNode = this;
        //PARA LOS RECOMENDADOS VECINOS
        if (stopwords.find(word) != stopwords.end()) {
            continue;
        }
        for (char c: word) {
            int index;
            if (!isalnum(c)) { continue; }
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
            auto *nodeMovie = dynamic_cast<TrieNodeVector *>(currentNode->childNode[36]);
            if (nodeMovie) {
                for (auto &mov: nodeMovie->vectorPelis) {
                    myMoviesMap[mov]++;
                }
            }
        }
    }
    return myMoviesMap;
}
void TrieNode::insert_movies_synopsis(const std::string& key, Movie* mov) {
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

void TrieNode::insert_movies_important(const std::string& key, Movie* mov) {
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