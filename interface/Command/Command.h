#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <memory>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual std::string getText() const = 0;
    virtual std::unique_ptr<Command> clone() const = 0;
};

class Option1 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "Option 1"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<Option1>(*this); }
};

class Option2 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "Option 2"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<Option2>(*this); }
};

class ExitOption : public Command {
public:
    void execute() override;
    std::string getText() const override { return "Exit"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<ExitOption>(*this); }
};

class SubOption1 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubOption 1"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubOption1>(*this); }
};

class SubOption2 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubOption 2"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubOption2>(*this); }
};

class SubOption3 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubOption 3"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubOption3>(*this); }
};

class SubOption4 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubOption 4"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubOption4>(*this); }
};

class SubOption5 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubOption 5"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubOption5>(*this); }
};

class SubSubOption1 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubSubOption 1"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubSubOption1>(*this); }
};

class SubSubOption2 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubSubOption 2"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubSubOption2>(*this); }
};

class SubSubOption5 : public Command {
public:
    void execute() override;
    std::string getText() const override { return "SubSubOption 5"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<SubSubOption5>(*this); }
};

class ReturnOption : public Command {
public:
    void execute() override;
    std::string getText() const override { return "Return"; }
    std::unique_ptr<Command> clone() const override { return std::make_unique<ReturnOption>(*this); }
};

#endif // COMMAND_H
