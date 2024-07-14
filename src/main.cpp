#include <iostream>
#include "app/Movie/Movie.h"
#include "app/TriePrefix/TrieNode.h"


using namespace std;

int main(){
    Movie a = Movie("BADIGAMER", "synopsis", {"horror", "action"});
    Movie b = Movie("LASaventurasDelPequenhoPAca", "synopsis", {"horror", "suspense"});

    auto* root = new TrieNode();

    for (const auto & it : a.getTags()) {
        insert_key(root, it, &a);
    }

    for (const auto & it : b.getTags()) {
        insert_key(root, it, &b);
    }


    cout << "Hello, World!" << endl;
    vector<Movie*> movies = search_key(root,  "suspense");
    for (auto & movie : movies) {
        cout << movie->getTitle() << endl;

    }






}
