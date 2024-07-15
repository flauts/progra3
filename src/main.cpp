#include <iostream>
#include <fstream>
#include "app/TriePrefix/TrieNode.h"
#include <unordered_set>
#include "app/Movie/Movie.h"
#include "app/SearchEngine/SearchEngineBuilder.h"
#include "tools/Utils.h"
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main(){
    fs::path projectDir = fs::absolute(fs::path(__FILE__).parent_path().parent_path());

    auto* TrieTitle = new TrieNode();
    auto* TrieSynopsis = new TrieNode();
    auto* TrieTags = new TrieNode();
    std::unordered_set<Movie*> movies;

    std::ifstream database(projectDir/"datos.csv");

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
            auto* new_movie = new Movie(id,title, synopsis, tags);
            movies.insert(new_movie);
            TrieSynopsis->insert_movies_synopsis(synopsis, new_movie);
            TrieTitle->insert_movies_title(title, new_movie);
            TrieTags->insert_movies_synopsis(tags, new_movie);
        }
    }

    bool active = true;
    SearchEngineBuilder searchEngineBuilder(TrieTitle, TrieSynopsis, TrieTags);
    while(active){
        int input;
        std::cout<<"1. Ingrese la busqueda"<<std::endl;
        std::cout<<"2. Ingrese los tags"<<std::endl;
        std::cout<<"3. Buscar"<<std::endl;
        std::cin >> input;
        std::cin.ignore();
        switch (input) {
            case 1: {
                std::string query;
                std::getline(std::cin, query);
                searchEngineBuilder.Query(query);
                break;}
            case 2:{
                std::string tags;
                std::getline(std::cin, tags);
                searchEngineBuilder.Tags(tags);
                break;
            }
            case 3:
                std::cout<<"buscando"<<std::endl;
                active = false;
                break;

        }
    }
    std::ofstream outFile(projectDir/"tags.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1; // O manejar el error como prefieras
    }

    for (auto movie : searchEngineBuilder.build()->get()) {
        outFile << *movie << std::endl;
    }

    active = true;
    while(active) {
        int input;
        std::cout<<"1. Siguiente pagina"<<std::endl;
        std::cout<<"2. Siguiente pagina"<<std::endl;
        std::cin >> input;
        switch (input) {
            case 1:
                searchEngineBuilder.getNextPage();
                for (auto movie : searchEngineBuilder.build()->get()) {
                    outFile << *movie << std::endl;
                }
                break;
            case 2:
                searchEngineBuilder.getBeforePage();
                for (auto movie : searchEngineBuilder.build()->get()) {
                    outFile << *movie << std::endl;
                }

                break;
            case 3:
                active = false;
                break;
        }
    }

    outFile.close();


    for (auto movie : movies) {
        delete movie;
    }

    delete TrieTitle;
    delete TrieSynopsis;
    delete TrieTags;

    return 0;
}