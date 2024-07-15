#include "Command.h"
#include "Menu.h"

// Implementaciones de Option1
void Option1::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<SubOption1>());
    commands.push_back(std::make_unique<SubOption2>());
    commands.push_back(std::make_unique<SubOption5>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de Option2
void Option2::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<SubOption3>());
    commands.push_back(std::make_unique<SubOption4>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de ExitOption
void ExitOption::execute() {
    endwin();
    exit(0);
}

// Implementaciones de SubOption1
void SubOption1::execute() {
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<SubSubOption1>());
    commands.push_back(std::make_unique<SubSubOption2>());
    commands.push_back(std::make_unique<SubSubOption5>());
    commands.push_back(std::make_unique<ReturnOption>());
    Menu::getInstance().setCommands(std::move(commands));
}

// Implementaciones de SubOption2
void SubOption2::execute() {
    // Define actions for SubOption2
}

// Implementaciones de SubOption3
void SubOption3::execute() {
    // Define actions for SubOption3
}

// Implementaciones de SubOption4
void SubOption4::execute() {
    // Define actions for SubOption4
}

// Implementaciones de SubOption5
void SubOption5::execute() {
    // Define actions for SubOption5
}

// Implementaciones de SubSubOption1
void SubSubOption1::execute() {
    // Define actions for SubSubOption1
}

// Implementaciones de SubSubOption2
void SubSubOption2::execute() {
    // Define actions for SubSubOption2
}

// Implementaciones de SubSubOption5
void SubSubOption5::execute() {
    // Define actions for SubSubOption5
}

// Implementaciones de ReturnOption
void ReturnOption::execute() {
    Menu::getInstance().restoreState();
}
