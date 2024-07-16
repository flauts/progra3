#include <iostream>
#include <fstream>
#include "app/TriePrefix/TrieNode.h"
#include <unordered_set>
#include "app/Movie/Movie.h"
#include "app/SearchEngine/SearchEngineBuilder.h"
#include "tools/Utils.h"
#include <vector>
#include <filesystem>
#include <limits>

namespace fs = std::filesystem;

fs::path projectDir = fs::absolute(fs::path(__FILE__).parent_path().parent_path());

int getValidatedInput(int min, int max) {
    int input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opción no válida. Por favor, introduce un número entre " << min << " y " << max << "." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}

void writeWatchLaterMovieToFile(const Movie& movie) {
    std::ofstream file(projectDir/"watch_later.txt", std::ios::app); // Open in append mode
    if(file.is_open()) {
        file << movie.getId() << std::endl;
    }
    file.close();
}

void writeLikedMovieToFile(const Movie& movie) {
    std::ofstream file(projectDir / "liked_movies.txt", std::ios::app); // Open in append mode
    if (file.is_open()) {
        file << movie.getId() << std::endl;
    }
    file.close();
}

std::unordered_set<Movie*> readWatchLaterMovies(const std::unordered_set<Movie*>& allMovies) {
    std::unordered_set<Movie*> watchLaterMovies;
    std::ifstream file(projectDir/"watch_later.txt");
    std::string movieId;

    if (!file.is_open()) {
        std::cerr << "Failed to open watch_later.txt" << std::endl;
        return watchLaterMovies; // Return empty if file can't be opened
    }

    while (getline(file, movieId)) {
        for (auto* movie : allMovies) {
            if (movie->getId() == movieId) {
                watchLaterMovies.insert(movie);
                break; // Found the movie, no need to continue the inner loop
            }
        }
    }

    file.close();
    return watchLaterMovies;
}

std::unordered_set<std::string> readLikedTagMovies(const std::unordered_set<Movie*>& allMovies) {
    std::unordered_set<std::string> likedMoviesTag;
    std::ifstream file(projectDir/"liked_movies.txt");
    std::string movieId;

    if (!file.is_open()) {
        std::cerr << "Failed to open liked_movies.txt" << std::endl;
        return likedMoviesTag;
    }

    while (getline(file, movieId)) {
        for (auto* movie : allMovies) {
            if (movie->getId() == movieId) {
                for(const auto& tag : movie->getTags()){
                    likedMoviesTag.insert(tag);
                }
            }
        }
    }

    file.close();
    return likedMoviesTag;
}

std::unordered_set<Movie*> findSimilarMovies(const std::unordered_set<std::string>& likedMoviesTag, TrieNode& TrieTag) {
    std::unordered_set<Movie*> recommendations;
    std::vector<std::string> likedT(likedMoviesTag.begin(), likedMoviesTag.end());
    for(auto tag : likedMoviesTag){
        int i = 0;
        auto m = TrieTag.search_movies_by_tag(likedT);
        for (auto it = m.begin(); it != m.end() && i < 5; ++it, ++i) {
            recommendations.insert(it->first);
        }
    }
    return recommendations;
}

void moviePage(Movie& movie){
    std::cout << movie << std::endl;
    std::cout << "1. Like" << std::endl;
    std::cout << "2. Ver más tarde" << std::endl;
    std::cout << "3. Volver a la búsqueda" << std::endl;
    bool active = true;
    while(active) {
        int input = getValidatedInput(1, 3);
        switch (input) {
            case 1:
                writeLikedMovieToFile(movie);
                std::cout << "Le has dado like!" << std::endl;
                break;
            case 2:
                writeWatchLaterMovieToFile(movie);
                std::cout << "Agregado a ver más tarde!" << std::endl;
                break;
            case 3:
                active = false;
                break;
        }
    }
}

void selectingMovies(SearchEngineBuilder& searchEngineBuilder){
    bool second = true;
    while(second) {
        std::vector<Movie*> movie_list = searchEngineBuilder.build()->get();
        for(int i = 1; i <= 5; i++){
            std::cout << i << ". " << movie_list[i-1]->getTitle() << std::endl;
        }
        std::cout << "6. Siguiente página" << std::endl;
        std::cout << "7. Anterior página" << std::endl;
        std::cout << "8. Volver" << std::endl;
        int input = getValidatedInput(1, 8);
        switch (input) {
            case 1: case 2: case 3: case 4: case 5:
                moviePage(*movie_list[input-1]);
                break;
            case 6:
                searchEngineBuilder.NextPage();
                break;
            case 7:
                searchEngineBuilder.PreviousPage();
                break;
            case 8:
                second = false;
                break;
        }
    }
}

void Searching(SearchEngineBuilder& searchEngineBuilder){
    bool first = true;
    while(first){
        std::cout << "1. Ingrese la búsqueda" << std::endl;
        std::cout << "2. Ingrese los tags" << std::endl;
        std::cout << "3. Buscar" << std::endl;
        std::cout << "4. Volver" << std::endl;
        int input = getValidatedInput(1, 4);
        switch (input) {
            case 1: {
                std::string query;
                std::getline(std::cin >> std::ws, query);
                searchEngineBuilder.Query(query);
                break;
            }
            case 2: {
                std::string tags;
                std::getline(std::cin >> std::ws, tags);
                searchEngineBuilder.Tags(tags);
                break;
            }
            case 3:
                std::cout << "Buscando..." << std::endl;
                selectingMovies(searchEngineBuilder);
                break;
            case 4:
                first = false;
                break;
        }
    }
}

int menuSub() {
    std::cout << "1. Buscar" << std::endl;
    std::cout << "2. Ver más tarde" << std::endl;
    std::cout << "3. Recomendadas" << std::endl;
    std::cout << "4. Salir" << std::endl;
    return getValidatedInput(1, 4);
}

void menuMain(SearchEngineBuilder& searchEngineBuilder, const std::unordered_set<Movie*>& movies, TrieNode* TrieTags){
    bool active = true;
    while(active){
        int input = menuSub();
        switch (input) {
            case 1:
                Searching(searchEngineBuilder);
                break;
            case 2: {
                std::unordered_set<Movie*> watchLaterMovies = readWatchLaterMovies(movies);
                for (auto* movie : watchLaterMovies) {
                    std::cout << movie->getTitle() << std::endl;
                }
                break;
            }
            case 3: {
                std::unordered_set<std::string> likedMoviesTag = readLikedTagMovies(movies);
                std::unordered_set<Movie*> recommendations = findSimilarMovies(likedMoviesTag, *TrieTags);
                for (auto* movie : recommendations) {
                    std::cout << movie->getTitle() << std::endl;
                }
                break;
            }
            case 4:
                active = false;
                break;
        }
    }
}


int main(){
    auto* TrieTitle = new TrieNode();
    auto* TrieSynopsis = new TrieNode();
    auto* TrieTags = new TrieNode();
    SearchEngineBuilder searchEngineBuilder(TrieTitle, TrieSynopsis, TrieTags);
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
            auto* new_movie = new Movie(id, title, synopsis, tags);
            movies.insert(new_movie);
            TrieSynopsis->insert_movies_synopsis(synopsis, new_movie);
            TrieTitle->insert_movies_important(title, new_movie);
            TrieTags->insert_movies_important(tags, new_movie);
        }
    }

    menuMain(searchEngineBuilder, movies, TrieTags);

    for (auto movie : movies) {
        delete movie;
    }
    delete TrieTitle;
    delete TrieSynopsis;
    delete TrieTags;

    return 0;
}
