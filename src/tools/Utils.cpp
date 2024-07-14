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
}


