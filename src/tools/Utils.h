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

    std::string to_ascii(const std::string& input);
    std::vector<std::string> parseCSVLine(std::ifstream &file);

    std::string cleanString(const std::string &str);

    std::map<Movie*, int> gather(std::map<Movie *, int> &set1, const std::map<Movie *, int> &set2);

    template<typename T, typename...Ts>
    std::vector<Movie *> search(T arg, Ts... args);
};


#endif //PROGRA3_UTILS_H
