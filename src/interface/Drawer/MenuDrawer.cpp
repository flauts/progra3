#include "MenuDrawer.h"
#include "ncurses.h"
#include "AnimationManager.h"

void MenuDrawer::drawMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    clear();
    bkgd(COLOR_PAIR(1));

    AnimationManager::getInstance().drawStaticBorder();
    AnimationManager::getInstance().drawStaticAsciiArt();

    int maxWidth = 0;
    for (const auto& command : commands) {
        int commandWidth = static_cast<int>(command->getText().size());
        maxWidth = std::max(maxWidth, commandWidth);
    }
    maxWidth += 6; // Espacio para los bordes y el espacio entre opciones

    int totalHeight = AnimationManager::getInstance().getAsciiArtHeight(AnimationManager::getInstance().getAsciiArtLarge()) + static_cast<int>(commands.size()) * 5;

    int spaceBetween = (COLS - maxWidth * static_cast<int>(commands.size())) / (static_cast<int>(commands.size()) + 1);
    int totalCommandsWidth = maxWidth * static_cast<int>(commands.size()) + spaceBetween * (static_cast<int>(commands.size()) - 1);

    // Si no hay suficiente espacio horizontal para el menú vertical, usa el menú de texto vertical
    if (COLS < totalCommandsWidth) {
        drawVerticalTextMenu(commands, highlight);
    } else if (LINES < totalHeight) {
        // Si no hay suficiente espacio vertical para el menú vertical, usa el menú horizontal
        if (LINES < AnimationManager::getInstance().getAsciiArtHeight(AnimationManager::getInstance().getAsciiArtLarge()) + 10) {
            drawHorizontalTextMenu(commands, highlight);
        } else {
            drawHorizontalMenu(commands, highlight);
        }
    } else {
        drawVerticalMenu(commands, highlight);
    }
}

void MenuDrawer::drawVerticalTextMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    clear();
    bkgd(COLOR_PAIR(1));
    AnimationManager::getInstance().drawStaticBorder();

    mvprintw(0, (COLS - static_cast<int>(AnimationManager::getInstance().getAsciiArtText().size())) / 2, AnimationManager::getInstance().getAsciiArtText().c_str());
    int y = 2;
    for (size_t i = 0; i < commands.size(); ++i) {
        if (static_cast<int>(i) == highlight) {
            attron(COLOR_PAIR(5));
        } else {
            attron(COLOR_PAIR(4));
        }
        mvprintw(y++, (COLS - static_cast<int>(commands[i]->getText().size())) / 2, commands[i]->getText().c_str());
        if (static_cast<int>(i) == highlight) {
            attroff(COLOR_PAIR(5));
        } else {
            attroff(COLOR_PAIR(4));
        }
    }
    // Mover el cursor a la última letra de la opción resaltada
    move(y - 1, (COLS + static_cast<int>(commands[highlight]->getText().size())) / 2 - 1);
    refresh();
}

void MenuDrawer::drawHorizontalTextMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    clear();
    bkgd(COLOR_PAIR(1));
    AnimationManager::getInstance().drawStaticBorder();

    mvprintw(0, (COLS - static_cast<int>(AnimationManager::getInstance().getAsciiArtText().size())) / 2, AnimationManager::getInstance().getAsciiArtText().c_str());
    int y = 2;
    int totalWidth = 0;
    int maxWidth = 0;
    for (const auto& command : commands) {
        int commandWidth = static_cast<int>(command->getText().size());
        maxWidth = std::max(maxWidth, commandWidth);
    }
    maxWidth += 6; // Espacio para los bordes y el espacio entre opciones
    totalWidth = maxWidth * static_cast<int>(commands.size());

    int x = (COLS - totalWidth) / 2;
    for (size_t i = 0; i < commands.size(); ++i) {
        if (static_cast<int>(i) == highlight) {
            attron(COLOR_PAIR(5));
        } else {
            attron(COLOR_PAIR(4));
        }
        mvprintw(y, x, commands[i]->getText().c_str());
        x += maxWidth;
        if (static_cast<int>(i) == highlight) {
            attroff(COLOR_PAIR(5));
        } else {
            attroff(COLOR_PAIR(4));
        }
    }
    // Mover el cursor a la última letra de la opción resaltada
    move(y, x - 5);
    refresh();
}

void MenuDrawer::drawVerticalMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    AnimationManager::getInstance().drawStaticAsciiArt();
    int maxWidth = 0;
    for (const auto& command : commands) {
        maxWidth = std::max(maxWidth, static_cast<int>(command->getText().size()));
    }
    maxWidth += 6; // Espacio para los bordes y el espacio entre opciones

    int menuHeight = static_cast<int>(commands.size()) * 5;
    int y_offset = AnimationManager::getInstance().getAsciiArtHeight(AnimationManager::getInstance().getAsciiArtLarge()) + 1;
    int y = (LINES - (menuHeight + y_offset)) / 2 + y_offset;
    int spaceBetween = std::max(0, (LINES - y - menuHeight) / (static_cast<int>(commands.size()) - 1));

    // Ajustar y para que el menú comience una distancia spaceBetween más arriba
    y -= spaceBetween;

    for (size_t i = 0; i < commands.size(); ++i) {
        drawOptionBox(y + static_cast<int>(i) * (5 + spaceBetween), (COLS - maxWidth) / 2, commands[i]->getText(), static_cast<int>(i) == highlight, maxWidth);
    }

    int padding = (maxWidth - static_cast<int>(commands[highlight]->getText().size()) - 2) / 2;
    move(y + highlight * (5 + spaceBetween) + 1, (COLS - maxWidth) / 2 + padding + static_cast<int>(commands[highlight]->getText().size()) - 1 + 1);

    refresh();
}

void MenuDrawer::drawHorizontalMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    AnimationManager::getInstance().drawStaticAsciiArt();
    int maxWidth = 0;
    for (const auto& command : commands) {
        maxWidth = std::max(maxWidth, static_cast<int>(command->getText().size()));
    }
    maxWidth += 6; // Espacio para los bordes y el espacio entre opciones

    int spaceBetween = (COLS - maxWidth * static_cast<int>(commands.size())) / (static_cast<int>(commands.size()) + 1);
    int totalCommandsWidth = maxWidth * static_cast<int>(commands.size()) + spaceBetween * (static_cast<int>(commands.size()) - 1);

    int y_offset = AnimationManager::getInstance().getAsciiArtHeight(AnimationManager::getInstance().getAsciiArtLarge()) + 1; // Asegurarse de no superponer el logo
    int y = y_offset + (LINES - y_offset - 5) / 2;
    int totalCommandsHeight = 5;

    // Calcular la posición inicial x
    int x = (COLS - totalCommandsWidth) / 2;

    for (size_t i = 0; i < commands.size(); ++i) {
        drawOptionBox(y, x + static_cast<int>(i) * (maxWidth + spaceBetween), commands[i]->getText(), static_cast<int>(i) == highlight, maxWidth);
    }

    int padding = (maxWidth - static_cast<int>(commands[highlight]->getText().size()) - 2) / 2;
    move(y + 1, x + highlight * (maxWidth + spaceBetween) + padding + static_cast<int>(commands[highlight]->getText().size()) - 1 + 1);

    refresh();
}

void MenuDrawer::drawOptionBox(int y, int x, const std::string& text, bool highlight, int width) const {
    int pair = highlight ? 5 : 4;

    int padding = (width - static_cast<int>(text.size()) - 2) / 2;

    attron(COLOR_PAIR(pair)); // Usar color adecuado para la opción (resaltada o no)
    mvprintw(y, x, "+%s+", std::string(width - 2, '-').c_str());
    mvprintw(y + 1, x, "|%s%s%s|", std::string(padding, ' ').c_str(), text.c_str(), std::string(width - padding - static_cast<int>(text.size()) - 2, ' ').c_str());
    mvprintw(y + 2, x, "+%s+", std::string(width - 2, '-').c_str());
    attroff(COLOR_PAIR(pair));

    refresh();
}
