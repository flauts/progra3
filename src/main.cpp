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


int main(){
//    Movie a = Movie("title", "synopsis", "Horror, Action");
//    Movie b = Movie("title", "synopsis","Horror,Suspense");


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
