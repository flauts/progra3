#include <iostream>
#include <fstream>
#include "app/Movie/Movie.h"

int main() {
    bool active = true;
    std::fstream fin;
    fin.open("msp_full_data.csv", std::ios::in);

    while(active){
        std::cout << "Bienvenido a Movie Searcher Pro" << std::endl;
        std::cout << "1. Buscar peliculas" << std::endl;
        std::cout << "2. Ver peliculas recomendadas por like" << std::endl;
        std::cout << "3. Ver mas tarde" << std::endl;
        std::cout << "4. Salir" << std::endl;

        int input;
        std::cin>>input;

        switch (input) {
            case 1:
                //Buscar peliculas
                break;
            case 2:
                //Ver peliculas recomendadas por like;
                break;
            case 3:
                //Ver mas tarde;
                break;
            case 4:
                //salir
                active = false;
                break;

        }
    }

}