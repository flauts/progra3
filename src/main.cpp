#include "Menu.h"

int main() {
    AnimationManager::getInstance().drawLoadingBar(20);
    Menu::getInstance().run();
}
