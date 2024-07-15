#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
#include <memory>
#include "../Command/Command.h"

class Memento {
    friend class Menu; // Agregar la clase Menu como amiga
public:
    Memento(std::vector<std::unique_ptr<Command>> state) : state_(std::move(state)) {}

private:
    std::vector<std::unique_ptr<Command>> getState() {
        return std::move(state_);
    }

    std::vector<std::unique_ptr<Command>> state_;
};

#endif // MEMENTO_H
