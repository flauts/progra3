
#include "Movie.h"
#include <sstream>


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
    this->synopsis = synopsis;
    std::stringstream ss(tags);
    std::string t;
    char delimiter = ',';
    while (getline(ss, t, delimiter)) {
        this->tags.insert(t);
    };
}
