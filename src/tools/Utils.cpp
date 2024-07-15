#include "Utils.h"
#include <codecvt>
#include <locale>

std::unordered_set<std::string> Utils::loadStopwords(const std::string &filepath) {
        std::unordered_set<std::string> stopwords;
        std::ifstream file(filepath);
        std::string word;
        while (file >> word) {
            stopwords.insert(word);
        }
        return stopwords;
    }

std::string Utils::to_ascii(const std::string& input) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(input);

        std::string result;
        for (wchar_t c : wide) {
            if (c < 128) {
                if (std::isalnum(c) || c == ' ' || c == '.' || c == ',' || c == '!' || c == '?' || c == '-' || c == '_') {
                    if (std::isalpha(c)) {
                        result += std::tolower(static_cast<char>(c));
                    } else {
                        result += static_cast<char>(c);
                    }
                }
            } else {
                wchar_t normalized = std::towlower(c);
                if (normalized >= 0x00E0 && normalized <= 0x00FF) {
                    // Handle common Latin-1 Supplement characters
                    static const char* latin1_map = "aaaaaaaceeeeiiii"
                                                    "dnoooooouuuuythn"
                                                    "aaaaaaaceeeeiiii"
                                                    "dnoooooouuuuythy";
                    result += latin1_map[normalized - 0x00E0];
                }
                // Other non-ASCII characters are omitted
            }
        }

        return result;
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

std::string Utils::cleanString(const std::string& str) {
    std::string cleaned;
    for (char c : str) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

std::vector<std::string>Utils::parseCSVLine(std::ifstream& file) {
    std::vector<std::string> result;
    std::string field;
    bool inQuotes = false;
    char ch;

    while (file.get(ch)) {
        if (ch == '\"') {
            inQuotes = !inQuotes;
        } else if (ch == ',' && !inQuotes) {
            result.push_back(field);
            field.clear();
        } else if (ch == '\n' && !inQuotes) {
            if (!field.empty()) {
                result.push_back(field);
            }
            return result;
        } else {
            field += ch;
        }
    }

    if (!field.empty()) {
        result.push_back(field);
    }
    return result;
}



//void Utils::serializeTrie(const TrieNode *root, const std::string &filename) {
//    std::ofstream out(filename, std::ios::binary);
//    if (out.is_open()) {
//        root->serialize(out);
//        out.close();
//    } else {
//        std::cerr << "Unable to open file for writing: " << filename << std::endl;
//    }
//}

//
//TrieNode* Utils::deserializeTrie(const std::string &filename) {
//    std::ifstream in(filename, std::ios::binary);
//    if (in.is_open()) {
//        TrieNode* root = TrieNode::deserialize(in);
//        in.close();
//        return root;
//    } else {
//        std::cerr << "Unable to open file for reading: " << filename << std::endl;
//        return nullptr;
//    }
//}
