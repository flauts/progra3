//
// Created by jfpro on 13/07/24.
//

#include "Command.h"
#include <ncurses.h>

void Option1::execute() {
    clear();
    mvprintw(0, 0, "Opcion 1 seleccionada");
    refresh();
    getch();
}

void Option2::execute() {
    clear();
    mvprintw(0, 0, "Opcion 2 seleccionada");
    refresh();
    getch();
}
