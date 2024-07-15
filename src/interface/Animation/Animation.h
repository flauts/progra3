#ifndef ANIMATION_H
#define ANIMATION_H

#include <ncurses.h>
#include <thread>
#include <chrono>
#include <csignal>
#include <functional>

class Animation {
public:
    static void drawAsciiArt();
    static void drawStaticAsciiArt();
    static void drawBorderSnail();
    static void drawStaticBorder();
    static void handleResizeDuringAnimation(const std::function<void()>& animationFunc);
    static constexpr int n_lines = 8; // Altura del logo en ASCII
    static volatile sig_atomic_t resized; // Bandera de redimensión
};

#endif // ANIMATION_H
