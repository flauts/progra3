#include "Menu.h"
#include <ncurses.h>
#include <csignal>
#include <thread>
#include <chrono>

Menu Menu::instance;
bool Menu::firstTime = true;

const char* ascii_art[] = {
    "   _____ _                          _   _      _   ",
    "  / ____| |                        | \\ | |    | |  ",
    " | |    | |___   __ ___   _____ ___|  \\| | ___| |_ ",
    R"( | |    |  __ \ / _` \ \ / / _ \_  / . ` |/ _ \ __|)",
    " | |____| |  | | (_| |\\ V /  __// /| |\\  |  __/ |_ ",
    R"(  \_____|_|  |_|\__,_| \_/ \___/___|_| \_|\___|\__|)",
    "                                                   ",
    "                                                   "
};

constexpr int n_lines = std::size(ascii_art);
const char* options[] = {
    "1. Opcion 1",
    "2. Opcion 2",
    "3. Salir"
};

constexpr int n_options = std::size(options);

Menu::Menu() {
    initscr();
    start_color(); // Inicializa el uso de colores

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Fondo negro, texto blanco
    init_pair(2, COLOR_CYAN, COLOR_BLACK); // Texto cian brillante
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); // Texto magenta brillante
    init_pair(4, COLOR_GREEN, COLOR_BLACK); // Texto verde brillante para opciones
    init_pair(5, COLOR_BLACK, COLOR_WHITE); // Fondo blanco, texto negro para selección
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // Texto magenta para el borde

    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    bkgd(COLOR_PAIR(1)); // Establecer fondo negro

    // Configurar la señal de redimensionamiento
    signal(SIGWINCH, [](int) {
        endwin();
        refresh();
        clear();
        drawMenu(0); // Ajustar aquí para llamar a la instancia correcta
    });

    commands.push_back(make_unique<Option1>());
    commands.push_back(make_unique<Option2>());
}

Menu::~Menu() {
    endwin();
}

Menu& Menu::getInstance() {
    return instance;
}

void Menu::drawOptionBox(int y, int x, const char* text, bool highlight) {
    if (highlight) {
        attron(COLOR_PAIR(5));
    } else {
        attron(COLOR_PAIR(4) | A_BOLD);
    }

    mvprintw(y, x, "+---------------+");
    mvprintw(y + 1, x, "| %-13s |", text);
    mvprintw(y + 2, x, "+---------------+");

    if (highlight) {
        attroff(COLOR_PAIR(5));
    } else {
        attroff(COLOR_PAIR(4) | A_BOLD);
    }
}

void Menu::drawAsciiArt() {
    attron(COLOR_PAIR(2) | A_BOLD);
    for (int i = 0; i < n_lines; ++i) {
        mvprintw(i + 1, (COLS - 52) / 2, ascii_art[i]);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pausa de 100ms para animación
    }
    attroff(COLOR_PAIR(2) | A_BOLD);
}

void Menu::drawBorderSnail() {
    attron(COLOR_PAIR(6)); // Usar color magenta para el borde

    int x_start = 0;
    int y_start = 0;
    int x_end = COLS - 1;
    int y_end = LINES - 1;

    mvprintw(y_start, x_start, "+"); // Esquina superior izquierda
    refresh();

    while (x_start <= x_end && y_start <= y_end) {
        for (int i = x_start + 1; i <= x_end; ++i) {
            mvprintw(y_start, i, "-");
            move(y_start, i); // Mover el cursor durante la animación
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        mvprintw(y_start, x_end, "+"); // Esquina superior derecha
        refresh();
        y_start++;

        for (int i = y_start; i <= y_end; ++i) {
            mvprintw(i, x_end, "|");
            move(i, x_end); // Mover el cursor durante la animación
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        mvprintw(y_end, x_end, "+"); // Esquina inferior derecha
        refresh();
        x_end--;

        if (y_start <= y_end) {
            for (int i = x_end; i >= x_start; --i) {
                mvprintw(y_end, i, "-");
                move(y_end, i); // Mover el cursor durante la animación
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            mvprintw(y_end, x_start, "+"); // Esquina inferior izquierda
            refresh();
            y_end--;
        }

        if (x_start <= x_end) {
            for (int i = y_end; i >= y_start; --i) {
                mvprintw(i, x_start, "|");
                move(i, x_start); // Mover el cursor durante la animación
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if (y_start == 1) break; // Detener la animación al regresar a la esquina superior izquierda
            mvprintw(y_start, x_start, "+"); // Esquina superior izquierda
            refresh();
            x_start++;
        }
    }
    attroff(COLOR_PAIR(6));
}

void Menu::animateBackground() {
    clear();
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Asegurarse de que el borde sea consistente
    drawBorderSnail();

    // Mostrar el ASCII art línea por línea
    drawAsciiArt();

    int y = (LINES - (n_options * 4)) / 2 - 2; // Ajuste de posición vertical

    for (int i = 0; i < n_options; ++i) {
        drawOptionBox(y + i * 4, (COLS - 16) / 2, options[i], false);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    move(LINES - 1, COLS - 1); // Mover el cursor al lado derecho durante la animación
    refresh();
}

void Menu::drawMenu(const int highlight) {
    clear();
    bkgd(COLOR_PAIR(1));

    attron(COLOR_PAIR(6)); // Usar color magenta para el borde

    int x_start = 0;
    int y_start = 0;
    int x_end = COLS - 1;
    int y_end = LINES - 1;

    mvprintw(y_start, x_start, "+"); // Esquina superior izquierda
    mvprintw(y_start, x_end, "+"); // Esquina superior derecha
    mvprintw(y_end, x_start, "+"); // Esquina inferior izquierda
    mvprintw(y_end, x_end, "+"); // Esquina inferior derecha

    for (int i = x_start + 1; i <= x_end - 1; ++i) {
        mvprintw(y_start, i, "-");
        mvprintw(y_end, i, "-");
    }

    for (int i = y_start + 1; i <= y_end - 1; ++i) {
        mvprintw(i, x_start, "|");
        mvprintw(i, x_end, "|");
    }
    attroff(COLOR_PAIR(6));

    attron(COLOR_PAIR(2) | A_BOLD);
    for (int i = 0; i < n_lines; ++i) {
        mvprintw(i + 1, (COLS - 52) / 2, ascii_art[i]);
    }
    attroff(COLOR_PAIR(2) | A_BOLD);

    int y = (LINES - (n_options * 4)) / 2 - 2; // Ajuste de posición vertical

    for (int i = 0; i < n_options; ++i) {
        drawOptionBox(y + i * 4, (COLS - 16) / 2, options[i], i == highlight);
    }

    refresh();
}

void Menu::processInput(int& choice) const {
    move((LINES - (n_options * 4)) / 2 - 1 + choice * 4, (COLS - 16) / 2 + 2);
    switch (getch()) {
        case KEY_UP:
        case KEY_LEFT:
            if (choice == 0) {
                choice = n_options - 1;
            } else {
                choice--;
            }
            break;
        case KEY_DOWN:
        case KEY_RIGHT:
            if (choice == n_options - 1) {
                choice = 0;
            } else {
                choice++;
            }
            break;
        case 10: // Enter key
            switch (choice) {
                case 0:
                    commands[0]->execute();
                    break;
                case 1:
                    commands[1]->execute();
                    break;
                case 2:
                    endwin();
                    exit(0);
                default: break;
            }
            firstTime = true; // Permite la animación al regresar al menú
            break;

        default:; // No hacer nada
    }
}

[[noreturn]] void Menu::run() const {
    int choice = 0;

    if (firstTime) {
        animateBackground();
        firstTime = false;
    }

    while (true) {
        drawMenu(choice);
        processInput(choice);
    }
}
