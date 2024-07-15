#ifndef MENU_H
#define MENU_H

#include <memory>
#include <stack>
#include <ncurses.h>
#include "Command.h"
#include "Memento.h"
#include "AnimationManager.h"
#include "../Drawer/MenuDrawer.h"
#include <vector>

class Menu {
public:
    static Menu& getInstance();
    [[noreturn]] void run();
    void setCommands(std::vector<std::unique_ptr<Command>> commands);

private:
    Menu();
    ~Menu();
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

    void saveState();
    void restoreState();
    void drawMenu(int highlight) const;
    void processInput(int& choice);

    static Menu instance;
    static bool firstTime;
    std::vector<std::unique_ptr<Command>> commands;
    std::stack<Memento> history;
    int highlight;
    mutable bool isVertical; // Variable para almacenar la disposición del menú

    MenuDrawer menuDrawer;  // Instancia de MenuDrawer

    friend class ReturnOption; // Asegúrate de que ReturnOption pueda acceder a los métodos privados de Menu
};

#endif // MENU_H
