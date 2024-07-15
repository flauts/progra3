#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <memory>
#include <iostream>
#include <unistd.h>  // For sleep

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual std::string getText() const = 0;
    virtual std::unique_ptr<Command> clone() const = 0;
};

// Primary options
class SearchOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Search"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchOption>(*this); }
};

class CheckBookmarksOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Check bookmarks"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<CheckBookmarksOption>(*this); }
};

class SeeMoreOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "See more..."; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SeeMoreOption>(*this); }
};

class ExitOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Exit"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<ExitOption>(*this); }
};

// SubOptions for SearchOption
class SearchByTagsSubOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Search by Tags"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchByTagsSubOption>(*this); }
};

class SearchByNameSubOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Search by Name"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchByNameSubOption>(*this); }
};

class SearchBySynopsisSubOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Search by Synopsis"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<SearchBySynopsisSubOption>(*this); }
};

// SubOptions for CheckBookmarksOption
class WatchLaterOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Watch Later list"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<WatchLaterOption>(*this); }
};

class FavoritesOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Favorites list"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<FavoritesOption>(*this); }
};

class WhatIsChavezNetOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "What is ChavezNet?"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<WhatIsChavezNetOption>(*this); }
};

// Return options for submenus
class ReturnOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Return"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<ReturnOption>(*this); }
};

// Confirm option for general usage
class ConfirmOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Confirm"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<ConfirmOption>(*this); }
};

// Option for the DevMode engage
class DevModeOption : public Command {
public:
    void execute() override;
    [[nodiscard]] std::string getText() const override { return "Engage DevMode"; }
    [[nodiscard]] std::unique_ptr<Command> clone() const override { return std::make_unique<DevModeOption>(*this); }

private:
    static bool authenticate();
    void displayDebugInfo();
    void showResourceUsage();
};

#endif // COMMAND_H
