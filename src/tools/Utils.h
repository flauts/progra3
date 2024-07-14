#ifndef PROGRA3_UTILS_H
#define PROGRA3_UTILS_H

#include <unordered_set>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


namespace Utils {
    std::unordered_set<std::string> loadStopwords(const std::string& filepath);
    std::vector<std::string> formatTags(const std::string& tags);
};


#endif //PROGRA3_UTILS_H
