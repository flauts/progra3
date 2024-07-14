#include "Movie.h"
#include <sstream>
#include <utility>
#include <unordered_set>

Movie::Movie(std::string  title, std::string  synopsis, const std::string& tags){
    this->title = title;
    this->synopsis= synopsis;
    std::unordered_set<std::string> tag;
    std::string t;
    std::stringstream ss(tags);
    char delimiter = ',';
    while (getline(ss, t, delimiter)) {
        tag.insert(t);
    }
    this->tags=tag;

}

std::unordered_set<std::string> Movie::getTags() const {
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

