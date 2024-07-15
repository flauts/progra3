#include "Menu.h"
#include "Animation.h"
#include <ncurses.h>
#include <csignal>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>

Menu Menu::instance;
bool Menu::firstTime = true;

Menu::Menu() : highlight(0) {
    initscr();
    start_color(); // Inicializa el uso de colores

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Fondo negro, texto blanco
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK); // Texto morado para la animacion
    init_pair(3, COLOR_CYAN, COLOR_BLACK); // Texto celeste despues de la animacion
    init_pair(4, COLOR_GREEN, COLOR_BLACK); // Texto verde brillante para opciones
    init_pair(5, COLOR_BLACK, COLOR_WHITE); // Fondo blanco, texto negro para seleccion
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // Texto morado para el borde

    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    bkgd(COLOR_PAIR(1)); // Establecer fondo negro

    // Configurar la señal de redimensionamiento
    signal(SIGWINCH, [](int) {
        endwin();
        refresh();
        clear();
        Menu::getInstance().drawMenu(0);
    });
}

Menu::~Menu() {
    endwin();
}

Menu& Menu::getInstance() {
    return instance;
}

[[noreturn]] void Menu::run() {
    int choice = 0;

    if (firstTime) {
        Animation::drawBorderSnail();
        Animation::drawAsciiArt();
        firstTime = false;
    }

    std::vector<std::unique_ptr<Command>> mainCommands;
    mainCommands.push_back(std::make_unique<Option1>());
    mainCommands.push_back(std::make_unique<Option2>());
    mainCommands.push_back(std::make_unique<ExitOption>());

    setCommands(std::move(mainCommands));
    highlight = static_cast<int>(commands.size()) - 1; // Resaltar la última opción al iniciar

    while (true) {
        drawMenu(highlight);
        processInput(highlight);
    }
}

void Menu::setCommands(std::vector<std::unique_ptr<Command>> newCommands) {
    saveState();
    commands = std::move(newCommands);
    highlight = 0; // Reset highlight to first option
}

void Menu::saveState() {
    std::vector<std::unique_ptr<Command>> stateCopy;
    for (auto& command : commands) {
        stateCopy.push_back(command->clone());
    }
    history.push(Memento(std::move(stateCopy)));
}

void Menu::restoreState() {
    if (!history.empty()) {
        commands = history.top().getState();
        history.pop();
    }
    highlight = static_cast<int>(commands.size()) - 1; // Seleccionar la última opción por defecto
}

void Menu::drawMenu(int highlight) const {
    clear();
    bkgd(COLOR_PAIR(1));

    Animation::drawStaticBorder();
    if (firstTime) {
        Animation::drawAsciiArt();
    } else {
        Animation::drawStaticAsciiArt();
    }

    int maxWidth = 0;
    for (const auto& command : commands) {
        maxWidth = std::max(maxWidth, static_cast<int>(command->getText().size()));
    }
    maxWidth += 4; // Espacio para los bordes

    int menuHeight = static_cast<int>(commands.size()) * 4;
    int y = (LINES - (menuHeight + Animation::n_lines)) / 2 + Animation::n_lines; // Centrar el menú verticalmente teniendo en cuenta el alto del logo

    for (size_t i = 0; i < commands.size(); ++i) {
        drawOptionBox(y + static_cast<int>(i) * 4, (COLS - maxWidth) / 2, commands[i]->getText(), static_cast<int>(i) == highlight, maxWidth);
    }

    // Mover el cursor a la última letra de la opción resaltada, desplazado una posición hacia la derecha
    int padding = (maxWidth - static_cast<int>(commands[highlight]->getText().size()) - 2) / 2;
    move(y + highlight * 4 + 1, (COLS - maxWidth) / 2 + padding + static_cast<int>(commands[highlight]->getText().size()) - 1 + 1);

    refresh();
}

void Menu::drawOptionBox(int y, int x, const std::string& text, bool highlight, int width) const {
    int pair = highlight ? 5 : 4;

    int padding = (width - static_cast<int>(text.size()) - 2) / 2;

    attron(COLOR_PAIR(pair)); // Usar color adecuado para la opción (resaltada o no)
    mvprintw(y, x, "+%s+", std::string(width - 2, '-').c_str());
    mvprintw(y + 1, x, "|%s%s%s|", std::string(padding, ' ').c_str(), text.c_str(), std::string(width - text.size() - padding - 2, ' ').c_str());
    mvprintw(y + 2, x, "+%s+", std::string(width - 2, '-').c_str());
    attroff(COLOR_PAIR(pair));
}

void Menu::processInput(int& choice) {
    int ch = getch();
    switch (ch) {
        case KEY_UP:
        case KEY_LEFT:
            if (choice == 0) {
                choice = static_cast<int>(commands.size()) - 1;
            } else {
                choice--;
            }
            break;
        case KEY_DOWN:
        case KEY_RIGHT:
            if (choice == static_cast<int>(commands.size()) - 1) {
                choice = 0;
            } else {
                choice++;
            }
            break;
        case 10: // Enter key
            commands[choice]->execute();
            break;
        default:
            break;
    }
}
