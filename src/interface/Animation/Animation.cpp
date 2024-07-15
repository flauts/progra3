#include "Animation.h"
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <csignal>

const char* ascii_art[] = {
    "   _____ _                          _   _      _   ",
    "  / ____| |                        | \\ | |    | |  ",
    " | |    | |___   __ ___   _____ ___|  \\| | ___| |_ ",
    " | |    |  __ \\ / _` \\ \\ / / _ \\_  / . ` |/ _ \\ __|",
    " | |____| |  | | (_| |\\ V /  __// /| |\\  |  __/ |_ ",
    "  \\_____|_|  |_|\\__,_| \\_/ \\___/___|_| \\_|\\___|\\__|",
    "                                                   ",
    "                                                   "
};

constexpr int n_lines = std::size(ascii_art);

void Animation::drawBorderSnail() {
    // Desactivar la señal de redimensionamiento
    auto old_handler = signal(SIGWINCH, SIG_IGN);

    attron(COLOR_PAIR(6)); // Usar color morado para el borde

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

    // Restaurar la señal de redimensionamiento
    signal(SIGWINCH, old_handler);
}

void Animation::drawAsciiArt() {
    attron(COLOR_PAIR(2) | A_BOLD); // Color morado durante la animación
    for (int i = 0; i < n_lines; ++i) {
        mvprintw(i + 1, (COLS - 52) / 2, ascii_art[i]);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pausa de 100ms para animación
    }
    attroff(COLOR_PAIR(2) | A_BOLD);
}

void Animation::drawStaticAsciiArt() {
    attron(COLOR_PAIR(3) | A_BOLD); // Color celeste después de la animación
    for (int i = 0; i < n_lines; ++i) {
        mvprintw(i + 1, (COLS - 52) / 2, ascii_art[i]);
    }
    attroff(COLOR_PAIR(3) | A_BOLD);
}

void Animation::drawStaticBorder() {
    attron(COLOR_PAIR(6));
    int x_start = 0;
    int y_start = 0;
    int x_end = COLS - 1;
    int y_end = LINES - 1;

    // Superior
    mvhline(y_start, x_start + 1, '-', x_end - 1);

    // Inferior
    mvhline(y_end, x_start + 1, '-', x_end - 1);

    // Izquierda
    mvvline(y_start + 1, x_start, '|', y_end - 1);

    // Derecha
    mvvline(y_start + 1, x_end, '|', y_end - 1);

    // Esquinas
    mvprintw(y_start, x_start, "+");
    mvprintw(y_start, x_end, "+");
    mvprintw(y_end, x_start, "+");
    mvprintw(y_end, x_end, "+");

    attroff(COLOR_PAIR(6));
    refresh();
}
