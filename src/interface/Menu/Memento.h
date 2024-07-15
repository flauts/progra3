#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
#include <memory>
#include "../Command/Command.h"

class Memento {
    friend class Menu; // Agregar la clase Menu como amiga
public:
    Memento(int highlight, std::vector<std::unique_ptr<Command>>&& commands)
        : highlight_(highlight), commands_(std::move(commands)) {}

private:
    int getHighlight() const {
        return highlight_;
    }

    const std::vector<std::unique_ptr<Command>>& getCommands() const {
        return commands_;
    }

    std::vector<std::unique_ptr<Command>> releaseCommands() {
        return std::move(commands_);
    }

    int highlight_;
    std::vector<std::unique_ptr<Command>> commands_;
};

#endif // MEMENTO_H
