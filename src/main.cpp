#include <iostream>
#include <fstream>
#include "app/TriePrefix/TrieNode.h"
#include <unordered_map>
#include <unordered_set>
#include "app/Movie/Movie.h"
#include "app/SearchEngine/SearchEngineBuilder.h"
#include <cstring>
#include "tools/Utils.h"



int main() {
    ifstream database("C:\\Users\\flauta\\progra3\\proyecto\\progra3\\datos.csv");
    if(!database.is_open()) {
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        return 1;
    }

    auto* title_root = new TrieNode();


    unordered_set<Movie*> movies;

    while (database.peek() != EOF) {
        vector<string> fields = Utils::parseCSVLine(database);
        if(fields.size() >= 4) {
            string id = fields[0];
            string title = fields[1];
            string synopsis = fields[2];
            string tags = fields[3];

            string cleanedTitle = Utils::cleanString(title);
            auto* new_movie = new Movie(id,title, synopsis, tags);
            vector<std::string> good_tags = new_movie->getTags();
            movies.insert(new_movie);
            title_root->insert_movies_data(synopsis, new_movie);
            title_root->insert_movies_data(title, new_movie);
        }
    }
// Antes del bucle, abre un archivo de texto en modo de escritura
    std::ofstream outFile("C:\\Users\\flauta\\progra3\\proyecto\\progra3\\output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1; // O manejar el error como prefieras
    }

// Dentro del bucle, escribe en el archivo
    for (auto movie : title_root->search_movies_by_key("Walter White")) {
        outFile << *movie << std::endl;
    }

// Después del bucle, cierra el archivo
    outFile.close();

    SearchEngineBuilder searchEngineBuilder;

    SearchEngine* searchEngine = searchEngineBuilder.Query("whimsical").Tags("comedy, drama").build();


    for (auto movie : movies) {
        delete movie;
    }

    delete title_root;

    return 0;
}