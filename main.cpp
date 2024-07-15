#include <iostream>
#include <fstream>
#include "src/app/TriePrefix/TrieNode.h"
#include <unordered_set>
#include "src/app/Movie/Movie.h"
#include "src/tools/Utils.h"
#include "src/app/SearchEngine/SearchEngineBuilder.h"
#include <vector>

int main(){
    auto* TrieData = new TrieNode();
    auto* TrieTags = new TrieNode();
    std::unordered_set<Movie*> movies;

    SearchEngineBuilder searchEngineBuilder;

    std::ifstream database(R"(C:\Users\Badir\Documents\projects\Hopium\datos.csv)");
    if(!database.is_open()) {
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        return 1;
    }
    while (database.peek() != EOF) {
        std::vector<std::string> fields = Utils::parseCSVLine(database);
        if(fields.size() >= 4) {
            std::string id = fields[0];
            std::string title = fields[1];
            std::string synopsis = fields[2];
            std::string tags = fields[3];

            std::string cleanedTitle = Utils::cleanString(title);
            auto* new_movie = new Movie(id,title, synopsis, tags);
            std::vector<std::string> good_tags = new_movie->getTags();
            movies.insert(new_movie);

            TrieData->insert_movies_data(synopsis, new_movie);
            TrieData->insert_movies_data(title, new_movie);
            TrieTags->insert_movies_data(tags, new_movie);
        }
    }

    // Antes del bucle, abre un archivo de texto en modo de escritura
    std::ofstream outFile(R"(C:\Users\Badir\Documents\projects\Hopium\tags.txt)");
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1; // O manejar el error como prefieras
    }

// Dentro del bucle, escribe en el archivo
    for (auto movie : TrieData->search_movies_by_key("it")) {
        outFile << *movie.first << std::endl;
    }

// Después del bucle, cierra el archivo
    outFile.close();


    for (auto movie : movies) {
        delete movie;
    }

    delete TrieData;

    return 0;
}
