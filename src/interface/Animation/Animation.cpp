#include "Animation.h"

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

volatile sig_atomic_t Animation::resized = 0;
std::function<void()> current_animation_func;

void resizeHandler(int) {
    Animation::resized = 1;
    endwin();
    refresh();
    clear();
    if (current_animation_func) {
        current_animation_func();
    }
}

void Animation::handleResizeDuringAnimation(const std::function<void()>& animationFunc) {
    current_animation_func = animationFunc;
    auto old_handler = signal(SIGWINCH, resizeHandler);

    while (true) {
        Animation::resized = 0;
        animationFunc();
        if (!Animation::resized) break; // Salir del bucle si no ha habido redimensión
    }

    signal(SIGWINCH, old_handler);
}

void Animation::drawBorderSnail() {
    handleResizeDuringAnimation([]() {
        attron(COLOR_PAIR(6)); // Usar color morado para el borde

        int x_start = 0;
        int y_start = 0;
        int x_end = COLS - 1;
        int y_end = LINES - 1;

        mvprintw(y_start, x_start, "+"); // Esquina superior izquierda
        refresh();

        while (x_start <= x_end && y_start <= y_end) {
            for (int i = x_start + 1; i <= x_end; ++i) {
                if (Animation::resized) return;
                mvprintw(y_start, i, "-");
                move(y_start, i); // Mover el cursor durante la animación
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            mvprintw(y_start, x_end, "+"); // Esquina superior derecha
            refresh();
            y_start++;

            for (int i = y_start; i <= y_end; ++i) {
                if (Animation::resized) return;
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
                    if (Animation::resized) return;
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
                    if (Animation::resized) return;
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
    });
}

void Animation::drawAsciiArt() {
    handleResizeDuringAnimation([]() {
        attron(COLOR_PAIR(2) | A_BOLD); // Color morado durante la animación
        for (int i = 0; i < n_lines; ++i) {
            if (Animation::resized) return;
            mvprintw(i + 1, (COLS - 52) / 2, ascii_art[i]);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pausa de 100ms para animación
        }
        attroff(COLOR_PAIR(2) | A_BOLD);
    });
}

void Animation::drawStaticAsciiArt() {
    handleResizeDuringAnimation([]() {
        attron(COLOR_PAIR(3) | A_BOLD); // Color celeste después de la animación
        for (int i = 0; i < n_lines; ++i) {
            if (Animation::resized) return;
            mvprintw(i + 1, (COLS - 52) / 2, ascii_art[i]);
        }
        attroff(COLOR_PAIR(3) | A_BOLD);
    });
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
