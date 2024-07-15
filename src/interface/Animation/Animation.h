#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    static void drawAsciiArt();
    static void drawStaticAsciiArt();
    static void drawBorderSnail();
    static void drawStaticBorder();
    static constexpr int n_lines = 8; // Altura del logo en ASCII
};

#endif // ANIMATION_H
