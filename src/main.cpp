#include <iostream>
#include <fstream>
#include "app/Movie/Movie.h"
#include "app/TriePrefix/TrieNode.h"
#include <filesystem>


std::string cleanString(const string& str) {
    string cleaned;
    for (char c : str) {
        if (isalnum(c)) {
            cleaned += tolower(c);
        }
    }
    return cleaned;
}

<<<<<<< HEAD

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

=======

int main(){
//    Movie a = Movie("title", "synopsis", "Horror, Action");
//    Movie b = Movie("title", "synopsis","Horror,Suspense");
>>>>>>> main


    ifstream database("C:\\Users\\flauta\\progra3\\proyecto\\progra3\\datos.csv");
    string id;
    string title;
    string synopsis;
    string tags;

    if(!database.is_open()){
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        return 1;
    }
    TrieNode* title_root = new TrieNode();

    while(database.good()){
        getline(database, id, ',');
        getline(database, title, ',');
        getline(database, synopsis, ',');
        getline(database, tags, '\n');
//        cout << title << endl;
        title = cleanString(title);
        title_root->insert_key(title);
    }
    string a = "tje";
    title_root->search_key(a);

    return 0;

}
