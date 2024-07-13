#ifndef PROGRA3_MOVIE_H
#define PROGRA3_MOVIE_H
#include <string>
#include <unordered_set>

class Movie {
    std::string title;
    std::string synopsis;
    std::unordered_set<std::string> tags;
public:
    const std::string &getTitle() const;
    const std::string &getSynopsis() const;
    const std::unordered_set<std::string> &getTags() const;
    Movie(const std::string &title, const std::string &synopsis, const std::string &tags);
};


#endif //PROGRA3_MOVIE_H
