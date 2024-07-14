#include "Movie.h"
#include <sstream>
#include <utility>
#include <unordered_set>

Movie::Movie(std::string  title, std::string  synopsis, const std::string& tags){
    this->title = title;
    this->synopsis= synopsis;
    std::vector<std::string> tag;
    std::string t;
    std::stringstream ss(tags);
    char delimiter = ',';
    while (getline(ss, t, delimiter)) {
        tag.push_back(t);
    }
    this->tags=tag;

}

std::vector<std::string> Movie::getTags() const {
    return tags;
}


bool Movie::operator==(Movie &m) {
    return title == m.title;
}

Movie::~Movie() {
    tags.clear();
}

const std::string &Movie::getSynopsis() const {
    return synopsis;
}

const std::string &Movie::getTitle() const {
    return title;
}


std::ostream &operator<<(std::ostream &os, const Movie &movie) {
    os << "title: " << movie.title << "\nsynopsis: " << movie.synopsis << "\ntags: ";
    for (const std::string& tag : movie.tags) {
        os << tag << ", ";
    }
    os<<"\n";
    return os;
}

