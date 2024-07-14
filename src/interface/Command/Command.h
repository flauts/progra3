//
// Created by jfpro on 13/07/24.
//

#ifndef COMMAND_H
#define COMMAND_H

class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class Option1 final : public Command {
public:
    void execute() override;
};

class Option2 final : public Command {
public:
    void execute() override;
};

#endif // COMMAND_H

