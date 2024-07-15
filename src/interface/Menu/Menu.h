#ifndef MENU_H
#define MENU_H

#include <memory>
#include <stack>
#include <ncurses.h>
#include "Command.h"
#include "Memento.h"
#include "Animation.h"
#include <csignal>
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
    void drawOptionBox(int y, int x, const std::string& text, bool highlight, int width) const;
    void processInput(int& choice);

    static Menu instance;
    static bool firstTime;
    std::vector<std::unique_ptr<Command>> commands;
    std::stack<Memento> history;
    int highlight;

    friend ReturnOption;
};

#endif // MENU_H
