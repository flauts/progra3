#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

class Movie {
private:
    std::string title;
    std::string synopsis;
    std::vector<std::string> tags;

public:
    Movie(std::string  title, std::string  synopsis, const std::vector<std::string>& tags);

    std::vector<std::string> getTags() const;

    std::string getTitle() const;
};

#endif // MOVIE_H
