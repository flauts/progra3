//
// Created by jfpro on 13/07/24.
//

#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <vector>
#include <memory>
#include "../Command/Command.h"

class Menu {
public:
    static Menu& getInstance() {
        static Menu instance;
        return instance;
    }

    void run();

private:
    Menu() {
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);
    }

    ~Menu() {
        endwin();
    }

    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

    void drawMenu();
    void processInput(int ch);

    std::vector<std::unique_ptr<Command>> commands;
};

#endif // MENU_H
