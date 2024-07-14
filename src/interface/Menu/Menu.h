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

    static bool firstTime; // Declarar como estática

    std::vector<unique_ptr<Command>> commands;

    Menu();
    ~Menu();

    static void drawOptionBox(int y, int x, const char* text, bool highlight);

    static void drawAsciiArt();

    static void drawBorderSnail();

    static void animateBackground();

    static void drawMenu(int highlight);

    void processInput(int &choice) const;

public:
    static Menu& getInstance();

    [[noreturn]] void run() const;
};

#endif // MENU_H
