#include "Movie.h"
#include "../../tools/Utils.h"
#include <sstream>

Movie::Movie(std::string id,std::string  title, std::string  synopsis, const std::string& tags){
    this->id = id;
    this->title = title;
    this->synopsis= synopsis;
    auto tag = Utils::formatTags(tags);
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
