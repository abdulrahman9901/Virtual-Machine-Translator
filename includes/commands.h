#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string>
#include <unordered_map>

enum class CommandType {
    Add,
    Sub,
    Neg,
    Eq,
    Gt,
    Lt,
    And,
    Or,
    Not,
    Push,
    Pop,
    Label,
    Goto,
    If,
    Function,
    Return,
    All,
    Empty,
    If_Goto,
    Call
};

extern std::unordered_map<std::string, CommandType> CommandTypeDict;
struct Command {
    CommandType type = CommandType::Empty;
    std::string mem_seg = "";
    std::string label_name = "";
    std::string scope = "";
    int arg = 0;

    Command();
    Command(CommandType type);
    Command(CommandType type, std::string label_name);
    Command(CommandType type, std::string mem_seg, int arg);
    std::string get_key();

    inline bool isEmpty() { return type == CommandType::Empty; }
};
#endif