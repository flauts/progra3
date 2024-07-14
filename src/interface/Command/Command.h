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

class Option1Command final : public Command {
public:
    void execute() override;
};

class Option2Command final : public Command {
public:
    void execute() override;
};

#endif // COMMAND_H

