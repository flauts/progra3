#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
#include <unordered_set>
#include <ostream>

class Movie {
private:
    std::string title;
    std::string synopsis;
    std::vector<std::string> tags;

public:
    Movie() = default;
    Movie(std::string  title, std::string  synopsis, const std::string& tags);

    std::vector<std::string> getTags() const;

    const std::string &getSynopsis() const;

    const std::string &getTitle() const;

    bool operator==(Movie& m);

    friend std::ostream &operator<<(std::ostream &os, const Movie &movie);

    ~Movie();
};

namespace std {
    template <>
    struct hash<Movie> {
        std::size_t operator()(const Movie& movie) const {
            return hash<std::string>()(movie.getTitle());
        }
    };
}




#endif // MOVIE_H
