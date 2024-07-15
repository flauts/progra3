#include "Menu.h"
#include "AnimationManager.h"
#include <ncurses.h>
#include <algorithm>

Menu Menu::instance;
bool Menu::firstTime = true;

Menu::Menu() : highlight(0), isVertical(false), menuDrawer(*this) {
    initscr();
    start_color(); // Inicializa el uso de colores

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Fondo negro, texto blanco
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK); // Texto morado para la animacion
    init_pair(3, COLOR_CYAN, COLOR_BLACK); // Texto celeste después de la animacion
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
        getInstance().drawMenu(0);
    });
}

Menu::~Menu() {
    endwin();
}

Menu& Menu::getInstance() {
    return instance;
}

[[noreturn]] void Menu::run() {
    if (firstTime) {
        AnimationManager::getInstance().drawBorderSnail();
        AnimationManager::getInstance().drawAdaptiveAsciiArt();
        firstTime = false;
    }

    std::vector<std::unique_ptr<Command>> mainCommands;
    mainCommands.push_back(std::make_unique<Option1>());
    mainCommands.push_back(std::make_unique<Option2>());
    mainCommands.push_back(std::make_unique<ExitOption>());

    setCommands(std::move(mainCommands));
    highlight = 0;

    while (true) {
        endwin();
        refresh();
        clear();
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
    history.push(Memento(highlight, std::move(stateCopy)));
}

void Menu::restoreState() {
    if (!history.empty()) {
        commands = history.top().releaseCommands();
        highlight = history.top().getHighlight();
        history.pop();
    }
}

void Menu::drawMenu(int highlight) const {
    menuDrawer.drawMenu(commands, highlight); // Utiliza la clase MenuDrawer para dibujar el menú
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
