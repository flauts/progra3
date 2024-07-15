#include "Command.h"
#include "../Menu/Menu.h"
#include <iostream>

// Implementaciones de SearchOption
void SearchOption::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<SearchByTagsSubOption>());
    commands.push_back(std::make_unique<SearchByNameSubOption>());
    commands.push_back(std::make_unique<SearchBySynopsisSubOption>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de CheckBookmarksOption
void CheckBookmarksOption::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<WatchLaterOption>());
    commands.push_back(std::make_unique<FavoritesOption>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de SeeMoreOption
void SeeMoreOption::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<DevModeOption>());
    commands.push_back(std::make_unique<WhatIsChavezNetOption>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de ExitOption
void ExitOption::execute() {
    std::cout << "Exiting application..." << std::endl;
    exit(0);
}

// Implementaciones de SearchByTagsSubOption
void SearchByTagsSubOption::execute() {
    std::cout << "Executing Search by Tags" << std::endl;
}

// Implementaciones de SearchByNameSubOption
void SearchByNameSubOption::execute() {
    std::cout << "Executing Search by Name" << std::endl;
}

// Implementaciones de SearchBySynopsisSubOption
void SearchBySynopsisSubOption::execute() {
    std::cout << "Executing Search by Synopsis" << std::endl;
}

// Implementaciones de ReturnSubOption
void ReturnSubOption::execute() {
    Menu::getInstance().restoreState();
}

// Implementaciones de WatchLaterOption
void WatchLaterOption::execute() {
    std::cout << "Executing Watch Later Option" << std::endl;
}

// Implementaciones de FavoritesOption
void FavoritesOption::execute() {
    std::cout << "Executing Favorites Option" << std::endl;
}

// Implementaciones de DevModeOption
void DevModeOption::execute() {
    std::cout << "Executing DevMode Option" << std::endl;
}

// Implementaciones de WhatIsChavezNetOption
void WhatIsChavezNetOption::execute() {
    std::cout << "Executing What is ChavezNet Option" << std::endl;
}

// Implementaciones de ReturnOption
void ReturnOption::execute() {
    Menu::getInstance().restoreState();
}

