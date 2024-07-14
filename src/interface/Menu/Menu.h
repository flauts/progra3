//
// Created by jfpro on 13/07/24.
//

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>
#include "Command.h"

using std::unique_ptr, std::make_unique;

class Menu {
private:
    static Menu instance;

    std::vector<unique_ptr<Command>> commands;

    Menu();
    ~Menu();

public:
    static Menu& getInstance();

    static void drawMenu();

    void processInput(int choice) const;

    [[noreturn]] void run() const;
};

#endif // MENU_H
