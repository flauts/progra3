#ifndef PROGRA3_UTILS_H
#define PROGRA3_UTILS_H

#include <unordered_set>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "../app/TriePrefix/TrieNode.h"


namespace Utils {
    std::unordered_set<std::string> loadStopwords(const std::string& filepath);
    std::vector<std::string> formatTags(const std::string& tags);
    std::vector<std::string> splitString(const std::string& str);
    TrieNode* deserializeTrie(const std::string& filename);
    void serializeTrie(const TrieNode* root, const std::string& filename);

    std::string to_ascii(const std::string& input);
    std::vector<std::string> parseCSVLine(std::ifstream &file);

    std::string cleanString(const std::string &str);
};


#endif //PROGRA3_UTILS_H
