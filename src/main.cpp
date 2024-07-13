#include <iostream>
#include "app/Movie/Movie.h"
using namespace std;

int main(){
    Movie a = Movie("title", "synopsis", "tags,a.b,c");

    while(1){
        int input;
        cin>>input;
        switch(input){
            case 1:
            cout<<input<<"\n";
            default:
                cout<<"a";
        }
    }
}
