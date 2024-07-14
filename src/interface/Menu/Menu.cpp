//
// Created by jfpro on 13/07/24.
//

#include "Menu.h"

[[noreturn]] void Menu::run() {
    commands.push_back(std::make_unique<Option1Command>());
    commands.push_back(std::make_unique<Option2Command>());

    while (true) {
        drawMenu();
        const int choice = getch();
        processInput(choice);
    }
}

void Menu::drawMenu() {
    clear();
    mvprintw(0, 0, "Menu Principal:");
    mvprintw(1, 0, "1. Opcion 1");
    mvprintw(2, 0, "2. Opcion 2");
    mvprintw(3, 0, "3. Salir");
    refresh();
}

void Menu::processInput(const int ch) const {
    switch (ch) {
        case '1':
            commands[0]->execute();
        break;
        case '2':
            commands[1]->execute();
        break;
        case '3':
            exit(0);
        default:
            mvprintw(4, 0, "Opcion no valida");
        refresh();
        getch();
        break;
    }
}
