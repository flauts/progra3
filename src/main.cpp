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

void moviePage(Movie& movie){
    std::cout<<"Titulo: "<<movie.getTitle()<<std::endl;
    std::cout<<"Sinopsis: "<<movie.getSynopsis()<<std::endl;
    std::cout<<"Tags: "<<movie.getTags()<<std::endl;
    std::cout<<"1. Ver mas"<<std::endl;
    std::cout<<"2. Volver"<<std::endl;

}

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
    active = true;
    while(active) {
        std::vector<Movie*> movie_list = searchEngineBuilder.build()->get();
        for(int i = 1; i <= 5;i++){
            std::cout<<i<<". "<<movie_list[i-1]->getTitle()<<std::endl;
        }
        std::cout<<"6. Siguiente pagina"<<std::endl;
        std::cout<<"7. Anterior pagina"<<std::endl;
        int input;
        std::cin >> input;
        std::cin.ignore();
        switch (input) {
            case 1:
                std::cout<<*movie_list[input-1]<<std::endl;
                break;
            case 2:
                std::cout<<*movie_list[input-1]<<std::endl;
                break;
            case 3:
                std::cout<<*movie_list[input-1]<<std::endl;

                break;
            case 4:
                std::cout<<*movie_list[input-1]<<std::endl;
                break;
            case 5:
                std::cout<<*movie_list[input-1]<<std::endl;
                break;
            case 6:{
                searchEngineBuilder.NextPage();
                break;
            }
            case 7: {
                searchEngineBuilder.PreviousPage();
                break;
            }
            case 8:
                active = false;
                break;
        }
    }
    for (auto movie : movies) {
        delete movie;
    }

    delete TrieTitle;
    delete TrieSynopsis;
    delete TrieTags;

    return 0;
}