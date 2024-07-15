#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <vector>
#include <string>
#include <ncurses.h>
#include <csignal>
#include <functional>
#include <thread>
#include <chrono>

class AnimationManager {
public:
    static AnimationManager& getInstance();
    void drawStaticBorder() const;
    void drawStaticAsciiArt() const;
    void drawAdaptiveAsciiArt() const;
    void drawBorderSnail() const;
    void drawAsciiArt() const;

    const std::vector<std::string>& getAsciiArtLarge() const;
    const std::vector<std::string>& getAsciiArtMedium() const;
    const std::vector<std::string>& getAsciiArtSmall() const;
    const std::string& getAsciiArtText() const;
    int getAsciiArtHeight(const std::vector<std::string>& asciiArt) const;

    friend void resizeHandler(int);

private:
    AnimationManager() = default;
    void handleResizeDuringAnimation(const std::function<void()>& animationFunc) const;

    static const std::vector<std::string> ascii_art_large;
    static const std::vector<std::string> ascii_art_medium;
    static const std::vector<std::string> ascii_art_small;
    static const std::string ascii_art_text;

    static volatile sig_atomic_t resized;
    static std::function<void()> current_animation_func;
};

#endif // ANIMATIONMANAGER_H
