#include <iostream>
#include <fstream>
#include "app/TriePrefix/TrieNode.h"
#include <unordered_map>
#include <unordered_set>
#include "app/Movie/Movie.h"
#include <cstring>
using namespace std;

std::string cleanString(const string& str) {
    string cleaned;
    for (char c : str) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

std::vector<std::string> parseCSVLine(std::ifstream& file) {
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

int main() {
    ifstream database("C:\\Users\\flauta\\progra3\\proyecto\\progra3\\datos.csv");
    if(!database.is_open()) {
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        return 1;
    }

    TrieNode* title_root = new TrieNode();
    unordered_set<Movie*> movies;

    while (database.peek() != EOF) {
        vector<string> fields = parseCSVLine(database);
        if(fields.size() >= 4) {
            string id = fields[0];
            string title = fields[1];
            string synopsis = fields[2];
            string tags = fields[3];

            string cleanedTitle = cleanString(title);
            Movie* new_movie = new Movie(title, synopsis, tags);
            movies.insert(new_movie);
            insert_key(title_root, cleanedTitle, new_movie);
        }
    }

    string a = "tje";
    // title_root->search_key(a);

    // Clean up
    for (auto movie : movies) {
        delete movie;
    }
    delete title_root;

    return 0;
}