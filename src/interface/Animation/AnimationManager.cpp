#include "AnimationManager.h"

volatile sig_atomic_t AnimationManager::resized = 0;
std::function<void()> AnimationManager::current_animation_func;

const std::vector<std::string> AnimationManager::ascii_art_large = {
    "   _____ _                          _   _      _   ",
    "  / ____| |                        | \\ | |    | |  ",
    " | |    | |___   __ ___   _____ ___|  \\| | ___| |_ ",
    " | |    |  __ \\ / _` \\ \\ / / _ \\_  / . ` |/ _ \\ __|",
    " | |____| |  | | (_| |\\ V /  __// /| |\\  |  __/ |_ ",
    "  \\_____|_|  |_|\\__,_| \\_/ \\___/___|_| \\_|\\___|\\__|",
    "                                                   ",
    "                                                   "
};

const std::vector<std::string> AnimationManager::ascii_art_medium = {
    "  _____ _                _     _   _ ",
    " / ____| |              | |   | | | |",
    "| |    | |__   __ _  ___| | __| |_| |",
    "| |    | '_ \\ / _` |/ __| |/ / __| __|",
    "| |____| | | | (_| | (__|   <| |_| |_ ",
    " \\_____|_| |_|\\__,_|\\___|_|\\_\\\\__|\\__|",
    "                                      ",
    "                                      "
};

const std::vector<std::string> AnimationManager::ascii_art_small = {
    "  _____      _",
    " /  __ \\    | |",
    "| /  \\/ ___| |_",
    "| |    / _ \\ __|",
    "| \\__/\\  __/ |_",
    " \\____/\\___|\\__|",
    "                ",
    "                "
};

const std::vector<std::string> AnimationManager::ascii_art_text = {
    "ChavezNet"
};

AnimationManager& AnimationManager::getInstance() {
    static AnimationManager instance;
    return instance;
}

int AnimationManager::getAsciiArtHeight(const std::vector<std::string>& asciiArt) const {
    return static_cast<int>(asciiArt.size());
}

int AnimationManager::getAsciiArtWidth(const std::vector<std::string>& asciiArt) const {
    if (asciiArt.empty()) return 0;
    return static_cast<int>(asciiArt[0].size());
}

const std::vector<std::string>& AnimationManager::getAsciiArtLarge() const {
    return ascii_art_large;
}

const std::vector<std::string>& AnimationManager::getAsciiArtMedium() const {
    return ascii_art_medium;
}

const std::vector<std::string>& AnimationManager::getAsciiArtSmall() const {
    return ascii_art_small;
}

const std::vector<std::string>& AnimationManager::getAsciiArtText() const {
    return ascii_art_text;
}

void resizeHandler(int) {
    AnimationManager::resized = 1;
    endwin();
    refresh();
    clear();
    if (AnimationManager::current_animation_func) {
        AnimationManager::current_animation_func();
    }
}

void AnimationManager::handleResizeDuringAnimation(const std::function<void()>& animationFunc) const {
    current_animation_func = animationFunc;
    auto old_handler = signal(SIGWINCH, resizeHandler);

    while (true) {
        AnimationManager::resized = 0;
        animationFunc();
        if (!AnimationManager::resized) break; // Salir del bucle si no ha habido redimensión
    }

    signal(SIGWINCH, old_handler);
}

void AnimationManager::drawStaticAsciiArtLarge() const {
    const std::vector<std::string>& ascii_art = ascii_art_large;
    attron(COLOR_PAIR(3) | A_BOLD); // Color celeste después de la animación
    for (int i = 0; i < static_cast<int>(ascii_art.size()); ++i) {
        mvprintw(i + 1, (COLS - static_cast<int>(ascii_art.at(0).size())) / 2, ascii_art.at(i).c_str());
    }
    attroff(COLOR_PAIR(3) | A_BOLD);
    refresh();
}

void AnimationManager::drawStaticAsciiArtMedium() const {
    const std::vector<std::string>& ascii_art = ascii_art_medium;
    attron(COLOR_PAIR(3) | A_BOLD); // Color celeste después de la animación
    for (int i = 0; i < static_cast<int>(ascii_art.size()); ++i) {
        mvprintw(i + 1, (COLS - static_cast<int>(ascii_art.at(0).size())) / 2, ascii_art.at(i).c_str());
    }
    attroff(COLOR_PAIR(3) | A_BOLD);
    refresh();
}

void AnimationManager::drawStaticAsciiArtSmall() const {
    const std::vector<std::string>& ascii_art = ascii_art_small;
    attron(COLOR_PAIR(3) | A_BOLD); // Color celeste después de la animación
    for (int i = 0; i < static_cast<int>(ascii_art.size()); ++i) {
        mvprintw(i + 1, (COLS - static_cast<int>(ascii_art.at(0).size())) / 2, ascii_art.at(i).c_str());
    }
    attroff(COLOR_PAIR(3) | A_BOLD);
    refresh();
}

void AnimationManager::drawStaticAsciiArtText() const {
    const std::vector<std::string>& ascii_art = ascii_art_text;
    attron(COLOR_PAIR(3) | A_BOLD); // Color celeste después de la animación
    for (int i = 0; i < static_cast<int>(ascii_art.size()); ++ i) {
        mvprintw(i + 1, (COLS - static_cast<int>(ascii_art.at(0).size())) / 2, ascii_art.at(i).c_str());
    }
    attroff(COLOR_PAIR(3) | A_BOLD);
    refresh();
}

void AnimationManager::drawStaticAsciiArt() const {
    if (LINES <= getAsciiArtHeight(ascii_art_small) || COLS <= getAsciiArtWidth(ascii_art_small)) {
        drawStaticAsciiArtText();
    } else if (LINES <= getAsciiArtHeight(ascii_art_medium) || COLS <= getAsciiArtWidth(ascii_art_medium)) {
        drawStaticAsciiArtSmall();
    } else if (LINES <= getAsciiArtHeight(ascii_art_large) || COLS <= getAsciiArtWidth(ascii_art_large)) {
        drawStaticAsciiArtMedium();
    } else {
        drawStaticAsciiArtLarge();
    }
}

void AnimationManager::drawAdaptiveAsciiArtAnimation() const {
    handleResizeDuringAnimation([]() {
        attron(COLOR_PAIR(2) | A_BOLD); // Color morado durante la animación

        const std::vector<std::string>* ascii_art;
        if (LINES <= getInstance().getAsciiArtHeight(ascii_art_small) ||
            COLS <= getInstance().getAsciiArtWidth(ascii_art_small)) {
            ascii_art = &ascii_art_text;
        } else if (LINES <= getInstance().getAsciiArtHeight(ascii_art_medium) ||
                   COLS <= getInstance().getAsciiArtWidth(ascii_art_medium)) {
            ascii_art = &ascii_art_small;
        } else if (LINES <= getInstance().getAsciiArtHeight(ascii_art_large) ||
                   COLS <= getInstance().getAsciiArtWidth(ascii_art_large)) {
            ascii_art = &ascii_art_medium;
        } else {
            ascii_art = &ascii_art_large;
        }

        for (int i = 0; i < static_cast<int>(ascii_art->size()); ++i) {
            if (resized) return;
            mvprintw(i + 1, (COLS - static_cast<int>(ascii_art->at(0).size())) / 2, ascii_art->at(i).c_str());
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pausa de 100ms para animación
        }

        attroff(COLOR_PAIR(2) | A_BOLD);
        getInstance().drawStaticAsciiArt();
    });
}

void AnimationManager::drawStaticBorder() const {
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

void AnimationManager::drawBorderSnail() const {
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
                if (AnimationManager::resized) return;
                mvprintw(y_start, i, "-");
                move(y_start, i); // Mover el cursor durante la animación
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            mvprintw(y_start, x_end, "+"); // Esquina superior derecha
            refresh();
            y_start++;

            for (int i = y_start; i <= y_end; ++i) {
                if (AnimationManager::resized) return;
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
                    if (AnimationManager::resized) return;
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
                    if (AnimationManager::resized) return;
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
