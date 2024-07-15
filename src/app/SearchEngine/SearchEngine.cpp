#include "SearchEngine.h"

std::vector<Movie*> SearchEngine::get(){
    std::vector<Movie*> result;
    for(int i = page * 5; i < (page + 1) * 5; i++){
        if(i < movies.size()){
            result.push_back(movies[i]);
    }
        else{
            throw std::runtime_error("No more movies");
        }
    }
    return result;
}

