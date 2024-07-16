//
// Created by jorughen on 7/15/24.
//

#ifndef PROGRA33_MENUUTILS_H
#define PROGRA33_MENUUTILS_H

#include <iostream>
#include <filesystem>
#include "../app/Movie/Movie.h"
#include "../app/TriePrefix/TrieNode.h"
#include "../app/SearchEngine/SearchEngineBuilder.h"

namespace fs = std::filesystem;

int getValidatedInput(int min, int max);
void writeWatchLaterMovieToFile(const Movie& movie);
void writeLikedMovieToFile(const Movie& movie);
std::unordered_set<Movie*> readWatchLaterMovies(const std::unordered_set<Movie*>& allMovies);
std::unordered_set<std::string> readLikedTagMovies(const std::unordered_set<Movie*>& allMovies);
std::unordered_set<Movie*> findSimilarMovies(const std::unordered_set<std::string>& likedMoviesTag, TrieNode& TrieTag);
void moviePage(Movie& movie);
void selectingMovies(SearchEngineBuilder& searchEngineBuilder);
void Searching(SearchEngineBuilder& searchEngineBuilder);
int menuSub();
void menuMain(SearchEngineBuilder& searchEngineBuilder, const std::unordered_set<Movie*>& movies, TrieNode* TrieTags, const fs::path& projectDir);

#endif //PROGRA33_MENUUTILS_H
