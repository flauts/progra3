#include <iostream>
#include "app/Movie/Movie.h"
#include "app/TriePrefix/TrieNode.h"


using namespace std;

int main(){
    Movie a = Movie("title", "synopsis", {"horror", "action"});
    Movie b = Movie("title", "synopsis", {"horror", "suspense"});

    auto* root = new TrieNode();

    for (const auto & it : a.getTags()) {
        insert_key(root, it, &a);
    }


    cout << "Hello, World!" << endl;
//    vector<Movie*> movies = search_key(root, (string &) "Horror");
//    for (auto & movie : movies) {
//        cout << movie->getTitle() << endl;
//
//    }






}
