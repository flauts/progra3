#include "SearchEngine.h"

const std::string &SearchEngine::getQuery() const {
    return query;
}

const std::vector<std::string> &SearchEngine::getTags() const {
    return tags;
}

const std::vector<Movie *> SearchEngine::execute() {
    return std::vector<Movie *>();
}
