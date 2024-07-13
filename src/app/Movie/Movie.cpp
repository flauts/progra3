
#include "Movie.h"


const std::string &Movie::getSynopsis() const {
    return synopsis;
}

const std::unordered_set<std::string> &Movie::getTags() const {
    return tags;
}

const std::string &Movie::getTitle() const {
    return title;
}

Movie::Movie(const std::string &title, const std::string &synopsis, const std::string &tags){
    this->title = title;
    this->title = synopsis;
}
