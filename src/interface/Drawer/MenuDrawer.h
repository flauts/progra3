#ifndef MENUDRAWER_H
#define MENUDRAWER_H

#include <vector>
#include <memory>
#include "../Command/Command.h"
#include "../Animation/AnimationManager.h"

class Menu; // Declaración adelantada de la clase Menu

class MenuDrawer {
public:
    MenuDrawer(const Menu& menu) : menu(menu) {}
    void drawMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const;

private:
    const Menu& menu;

    void drawVerticalTextMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const;
    void drawHorizontalTextMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const;
    void drawVerticalMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const;
    void drawHorizontalMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const;
    void drawOptionBox(int y, int x, const std::string& text, bool highlight, int width) const;
};

#endif // MENUDRAWER_H
