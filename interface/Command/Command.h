#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <memory>
#include <iostream>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual std::string getText() const = 0;
    virtual std::unique_ptr<Command> clone() const = 0;
};

// Primary options = = = = =

class SearchOption : public Command {
public:
    void execute() override { std::cout << "Executing Search Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Search"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchOption>(*this); }
};

class CheckBookmarksOption : public Command {
public:
    void execute() override { std::cout << "Executing Check Bookmarks Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Check bookmarks"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<CheckBookmarksOption>(*this); }
};

class SeeMoreOption : public Command {
public:
    void execute() override { std::cout << "Executing See More Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "See more..."; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SeeMoreOption>(*this); }
};

class ExitOption : public Command {
public:
    void execute() override { std::cout << "Executing Exit Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Exit"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<ExitOption>(*this); }
};

// SubOptions for SearchOption = = = = =
class SearchByTagsSubOption : public Command {
public:
    void execute() override { std::cout << "Executing Search by Tags SubOption" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Search by Tags"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchByTagsSubOption>(*this); }
};

class SearchByNameSubOption : public Command {
public:
    void execute() override { std::cout << "Executing Search by Name SubOption" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Search by Name"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchByNameSubOption>(*this); }
};

class SearchBySynopsisSubOption : public Command {
public:
    void execute() override { std::cout << "Executing Search by Synopsis SubOption" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Search by Synopsis"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchBySynopsisSubOption>(*this); }
};

class ReturnSubOption : public Command {
public:
    void execute() override { std::cout << "Returning to Search Options" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Cancel"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<ReturnSubOption>(*this); }
};

// SubOptions for CheckBookmarksOption = = = = =
class WatchLaterOption : public Command {
public:
    void execute() override { std::cout << "Executing Watch Later Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Watch Later list"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<WatchLaterOption>(*this); }
};

class FavoritesOption : public Command {
public:
    void execute() override { std::cout << "Executing Favorites Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Favorites list"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<FavoritesOption>(*this); }
};

// SubOptions for SeeMoreOption = = = = =
class DevModeOption : public Command {
public:
    void execute() override { std::cout << "Executing DevMode Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "DevMode"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<DevModeOption>(*this); }
};

class WhatIsChavezNetOption : public Command {
public:
    void execute() override { std::cout << "Executing What is ChavezNet Option" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "What is ChavezNet?"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<WhatIsChavezNetOption>(*this); }
};

// Return options for submenus = = = = =
class ReturnOption : public Command {
public:
    void execute() override { std::cout << "Returning to Previous Menu" << std::endl; }
    [[nodiscard]] std::string getText() const override { return "Return"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<ReturnOption>(*this); }
};

#endif // COMMAND_H
