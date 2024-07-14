#include "Utils.h"

std::unordered_set<std::string> Utils::loadStopwords(const std::string &filepath) {
        std::unordered_set<std::string> stopwords;
        std::ifstream file(filepath);
        std::string word;
        while (file >> word) {
            stopwords.insert(word);
        }
        return stopwords;
    }

std::vector<std::string> Utils::formatTags(const std::string &tags) {
    std::vector<std::string> tag;
    std::string t;
    std::stringstream ss(tags);
    char delimiter = ',';
    while (getline(ss, t, delimiter)) {
        tag.push_back(t);
    }
    return tag;
}

std::vector<std::string> Utils::splitString(const std::string &str) {
    std::unordered_set<char> delimiters = {' ', ',', '.'};
    std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(str);
        while (std::getline(ss, token)) {
            std::string word;
            for (char c : token) {
                if (delimiters.find(c) != delimiters.end()) {
                    if (!word.empty()) {
                        tokens.push_back(word);
                        word.clear();
                    }
                } else {
                    word += c;
                }
            }
            if (!word.empty()) {
                tokens.push_back(word);
            }
        }
        return tokens;
    }



