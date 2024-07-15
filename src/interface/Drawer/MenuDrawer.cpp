#include "MenuDrawer.h"
#include "ncurses.h"
#include "AnimationManager.h"

const int BORDER_PADDING = 2; // Un borde a cada lado
const int ADDITIONAL_PADDING = 4; // Espacio adicional para presentación

void MenuDrawer::drawMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    clear();
    bkgd(COLOR_PAIR(1));

    AnimationManager::getInstance().drawStaticBorder();

    int maxWidth = 0;
    for (const auto& command : commands) {
        int commandWidth = static_cast<int>(command->getText().size());
        maxWidth = std::max(maxWidth, commandWidth);
    }
    maxWidth += BORDER_PADDING + ADDITIONAL_PADDING;

    int logoWidthSmall = AnimationManager::getInstance().getAsciiArtWidth(AnimationManager::getInstance().getAsciiArtSmall());
    int logoHeightSmall = AnimationManager::getInstance().getAsciiArtHeight(AnimationManager::getInstance().getAsciiArtSmall());

    int commandWidthWithPadding = maxWidth;
    int totalHeightVertical = logoHeightSmall + static_cast<int>(commands.size()) * 5;

    int verticalCommandWidth = maxWidth;
    int verticalCommandHeight = logoHeightSmall + static_cast<int>(commands.size()) * 3;

    int horizontalCommandWidth = maxWidth;
    int spaceBetweenHorizontal = (COLS - horizontalCommandWidth * static_cast<int>(commands.size())) / (static_cast<int>(commands.size()) + 1);
    int totalCommandsWidthHorizontal = horizontalCommandWidth * static_cast<int>(commands.size()) + spaceBetweenHorizontal * (static_cast<int>(commands.size()) - 1);
    int totalHeightHorizontal = logoHeightSmall + 5;

    if (COLS <= verticalCommandWidth) {
        drawVerticalTextMenu(commands, highlight);
    } else if (LINES <= totalHeightVertical) {
        if (LINES <= totalHeightHorizontal) {
            drawHorizontalTextMenu(commands, highlight);
        } else {
            if (COLS <= totalCommandsWidthHorizontal) {
                drawVerticalTextMenu(commands, highlight);
            } else {
                drawHorizontalMenu(commands, highlight);
            }
        }
    } else {
        drawVerticalMenu(commands, highlight);
    }
}

void MenuDrawer::drawVerticalTextMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    clear();
    bkgd(COLOR_PAIR(1));
    AnimationManager::getInstance().drawStaticBorder();

    int maxWidth = 0;
    for (const auto& command : commands) {
        int commandWidth = static_cast<int>(command->getText().size());
        maxWidth = std::max(maxWidth, commandWidth);
    }
    maxWidth += BORDER_PADDING + ADDITIONAL_PADDING;

    const std::vector<std::string>& asciiArtText = AnimationManager::getInstance().getAsciiArtText();
    int asciiArtTextWidth = static_cast<int>(asciiArtText[0].size());
    for (int i = 0; i < static_cast<int>(asciiArtText.size()); ++i) {
        mvprintw(i, (COLS - asciiArtTextWidth) / 2, asciiArtText[i].c_str());
    }

    int y = static_cast<int>(asciiArtText.size()) + 2;
    for (size_t i = 0; i < commands.size(); ++i) {
        int x = (COLS - static_cast<int>(commands[i]->getText().size())) / 2;
        if (static_cast<int>(i) == highlight) {
            attron(COLOR_PAIR(5));
        } else {
            attron(COLOR_PAIR(4));
        }
        mvprintw(y++, x, "%s", commands[i]->getText().c_str());

        if (static_cast<int>(i) == highlight) {
            attroff(COLOR_PAIR(5));
        } else {
            attroff(COLOR_PAIR(4));
        }
    }
    move(y - static_cast<int>(commands.size()) + highlight, (COLS - static_cast<int>(commands[highlight]->getText().size())) / 2 + static_cast<int>(commands[highlight]->getText().size()) - 1);
    refresh();
}

void MenuDrawer::drawHorizontalTextMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    clear();
    bkgd(COLOR_PAIR(1));
    AnimationManager::getInstance().drawStaticBorder();

    const std::vector<std::string>& asciiArtText = AnimationManager::getInstance().getAsciiArtText();
    int asciiArtTextWidth = static_cast<int>(asciiArtText[0].size());
    for (int i = 0; i < static_cast<int>(asciiArtText.size()); ++i) {
        mvprintw(i, (COLS - asciiArtTextWidth) / 2, asciiArtText[i].c_str());
    }

    int y = static_cast<int>(asciiArtText.size()) + 2;
    int totalWidth = 0;
    int maxWidth = 0;

    for (const auto& command : commands) {
        int commandWidth = static_cast<int>(command->getText().size());
        maxWidth = std::max(maxWidth, commandWidth);
    }
    maxWidth += BORDER_PADDING + ADDITIONAL_PADDING;
    totalWidth = maxWidth * static_cast<int>(commands.size());

    if (COLS <= totalWidth) {
        drawVerticalTextMenu(commands, highlight);
        return;
    }

    int x = (COLS - totalWidth) / 2;
    for (size_t i = 0; i < commands.size(); ++i) {
        int xCentered = x + (maxWidth - static_cast<int>(commands[i]->getText().size())) / 2;
        if (static_cast<int>(i) == highlight) {
            attron(COLOR_PAIR(5));
        } else {
            attron(COLOR_PAIR(4));
        }
        mvprintw(y, xCentered, "%s", commands[i]->getText().c_str());
        x += maxWidth;
        if (static_cast<int>(i) == highlight) {
            attroff(COLOR_PAIR(5));
        } else {
            attroff(COLOR_PAIR(4));
        }
    }
    move(y, (COLS - maxWidth * static_cast<int>(commands.size())) / 2 + highlight * maxWidth + (maxWidth - static_cast<int>(commands[highlight]->getText().size())) / 2 + static_cast<int>(commands[highlight]->getText().size()) - 1);
    refresh();
}

void MenuDrawer::drawVerticalMenu(const std::vector<std::unique_ptr<Command>>& commands, int highlight) const {
    AnimationManager::getInstance().drawStaticAsciiArt();
    int maxWidth = 0;

    for (const auto& command : commands) {
        maxWidth = std::max(maxWidth, static_cast<int>(command->getText().size()));
    }
    maxWidth += BORDER_PADDING + ADDITIONAL_PADDING;

    int menuHeight = static_cast<int>(commands.size()) * 5;
    int y_offset = AnimationManager::getInstance().getAsciiArtHeight(AnimationManager::getInstance().getAsciiArtLarge()) + 1;
    int y = (LINES - (menuHeight + y_offset)) / 2 + y_offset;
    int spaceBetween = std::max(0, (LINES - y - menuHeight) / (static_cast<int>(commands.size()) - 1));

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
    maxWidth += BORDER_PADDING + ADDITIONAL_PADDING;

    int spaceBetween = (COLS - maxWidth * static_cast<int>(commands.size())) / (static_cast<int>(commands.size()) + 1);
    int totalCommandsWidthHorizontal = maxWidth * static_cast<int>(commands.size()) + spaceBetween * (static_cast<int>(commands.size()) - 1);

    if (COLS <= totalCommandsWidthHorizontal) {
        drawVerticalTextMenu(commands, highlight);
        return;
    }

    int y_offset = AnimationManager::getInstance().getAsciiArtHeight(AnimationManager::getInstance().getAsciiArtLarge()) + 1;
    int y = y_offset + (LINES - y_offset - 5) / 2;
    int totalCommandsHeight = 5;

    int x = (COLS - totalCommandsWidthHorizontal) / 2;

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

    attron(COLOR_PAIR(pair));
    mvprintw(y, x, "+%s+", std::string(width - 2, '-').c_str());
    mvprintw(y + 1, x, "|%s%s%s|", std::string(padding, ' ').c_str(), text.c_str(), std::string(width - padding - static_cast<int>(text.size()) - 2, ' ').c_str());
    mvprintw(y + 2, x, "+%s+", std::string(width - 2, '-').c_str());
    attroff(COLOR_PAIR(pair));

    refresh();
}
