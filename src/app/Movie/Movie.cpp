#include "Movie.h"
#include "../../tools/Utils.h"
#include <sstream>
#include <utility>

Movie::Movie(std::string id,std::string  title, std::string  synopsis, const std::string& tags){
    this->id = std::move(id);
    this->title = std::move(title);
    this->synopsis= std::move(synopsis);
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

const std::string &Movie::getId() const {
    return id;
}
