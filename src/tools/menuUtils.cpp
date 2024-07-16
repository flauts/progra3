//
// Created by jorughen on 7/15/24.
//
#include <iostream>
#include <filesystem>
#include "../app/Movie/Movie.h"
#include "../app/SearchEngine/SearchEngineBuilder.h"
#include "menuUtils.h"

namespace fs = std::filesystem;


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

void writeWatchLaterMovieToFile(const Movie& movie, const fs::path& projectDir) {
    std::ofstream file(projectDir/"watch_later.txt", std::ios::app); // Open in append mode
    if(file.is_open()) {
        file << movie.getId() << std::endl;
    }
    file.close();
}

void writeLikedMovieToFile(const Movie& movie, const fs::path& projectDir) {
    std::ofstream file(projectDir / "liked_movies.txt", std::ios::app); // Open in append mode
    if (file.is_open()) {
        file << movie.getId() << std::endl;
    }
    file.close();
}

std::unordered_set<Movie*> readWatchLaterMovies(const std::unordered_set<Movie*>& allMovies, const fs::path& projectDir) {
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

std::unordered_set<std::string> readLikedTagMovies(const std::unordered_set<Movie*>& allMovies, fs::path projectDir) {
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

void moviePage(Movie& movie, const fs::path& projectDir){
    std::cout << movie << std::endl;
    std::cout << "1. Like" << std::endl;
    std::cout << "2. Ver más tarde" << std::endl;
    std::cout << "3. Volver a la búsqueda" << std::endl;
    bool active = true;
    while(active) {
        int input = getValidatedInput(1, 3);
        switch (input) {
            case 1:
                writeLikedMovieToFile(movie, projectDir);
                std::cout << "Le has dado like!" << std::endl;
                break;
            case 2:
                writeWatchLaterMovieToFile(movie, projectDir);
                std::cout << "Agregado a ver más tarde!" << std::endl;
                break;
            case 3:
                active = false;
                break;
        }
    }
}

void selectingMovies(SearchEngineBuilder& searchEngineBuilder,const fs::path& projectDir ){
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
                moviePage(*movie_list[input-1], projectDir);
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

void Searching(SearchEngineBuilder& searchEngineBuilder, const fs::path& projectDir){
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
                selectingMovies(searchEngineBuilder, projectDir);
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

void menuMain(SearchEngineBuilder& searchEngineBuilder, const std::unordered_set<Movie*>& movies, TrieNode* TrieTags, const fs::path& projectDir){
    bool active = true;
    while(active){
        int input = menuSub();
        switch (input) {
            case 1:
                Searching(searchEngineBuilder, projectDir);
                break;
            case 2: {
                std::unordered_set<Movie*> watchLaterMovies = readWatchLaterMovies(movies, projectDir);
                for (auto* movie : watchLaterMovies) {
                    std::cout << movie->getTitle() << std::endl;
                }
                break;
            }
            case 3: {
                std::unordered_set<std::string> likedMoviesTag = readLikedTagMovies(movies, projectDir);
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

