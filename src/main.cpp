#include <iostream>
#include <fstream>
#include "app/TriePrefix/TrieNode.h"
#include <unordered_map>
#include <unordered_set>
#include "app/Movie/Movie.h"
#include "app/SearchEngine/SearchEngineBuilder.h"
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
    ifstream database("/home/jorughen/Documents/progra3/datos.csv");
    if(!database.is_open()) {
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        return 1;
    }

    auto* title_root = new TrieNode();
    auto* tags_root = new TrieNode();


    unordered_set<Movie*> movies;

    while (database.peek() != EOF) {
        vector<string> fields = parseCSVLine(database);
        if(fields.size() >= 4) {
            string id = fields[0];
            string title = fields[1];
            string synopsis = fields[2];
            string tags = fields[3];

            string cleanedTitle = cleanString(title);
            string cleanedSynopsis = cleanString(synopsis);
            auto* new_movie = new Movie(id,title, synopsis, tags);
            vector<std::string> good_tags = new_movie->getTags();
            movies.insert(new_movie);
            title_root->insert_movies_data(synopsis, new_movie);
            title_root->insert_movies_data(title, new_movie);
            tags_root->insert_movies_data(tags, new_movie);
        }
    }
// Antes del bucle, abre un archivo de texto en modo de escritura
    std::ofstream outFile("/home/jorughen/Documents/progra3/resultados.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1; // O manejar el error como prefieras
    }

// Dentro del bucle, escribe en el archivo
    for (auto movie : title_root->search_movies_by_key("Walter Breaking White Bad")) {
        outFile << *movie << std::endl;
    }

// Después del bucle, cierra el archivo
    outFile.close();


    // Antes del bucle, abre un archivo de texto en modo de escritura
    std::ofstream outFile2("/home/jorughen/Documents/progra3/resultadosTag.txt");
    if (!outFile2.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1; // O manejar el error como prefieras
    }

// Dentro del bucle, escribe en el archivo
    for (auto movie : tags_root->search_movies_by_key("Horror Action")) {
        outFile2 << *movie << std::endl;
    }

// Después del bucle, cierra el archivo
    outFile2.close();





    SearchEngineBuilder searchEngineBuilder;

    SearchEngine* searchEngine = searchEngineBuilder.Query("whimsical").Tags("comedy, drama").build();


    for (auto movie : movies) {
        delete movie;
    }

    delete title_root;




    return 0;
}