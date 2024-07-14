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

    [[noreturn]] void run();

    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

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


    static void drawMenu();
    void processInput(int ch) const;

    std::vector<std::unique_ptr<Command>> commands{};
};

#endif // MENU_H
