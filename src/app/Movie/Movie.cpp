#include "Movie.h"

#include <utility>

Movie::Movie(std::string  title, std::string  synopsis, const std::vector<std::string>& tags)
        : title(std::move(title)), synopsis(std::move(synopsis)), tags(tags) {}

std::vector<std::string> Movie::getTags() const {
    return tags;
}
std::string Movie::getTitle() const { // Definición del método getTitle
    return title;
}
