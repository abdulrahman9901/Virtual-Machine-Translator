#include "../includes/commands.h"
#include <iostream>

Command::Command() {}
Command::Command(CommandType type) : type(type) {}
Command::Command(CommandType type, std::string label_name)
    : type(type), label_name(label_name) {}
Command::Command(CommandType type, std::string mem_seg, int arg)
    : type(type), mem_seg(mem_seg), arg(arg) {}

std::string Command::get_key() {
    for (auto& it : CommandTypeDict) {
        if (it.second == this->type) {
            return it.first;
        }
    }
    return "null";
}
std::unordered_map<std::string, CommandType> CommandTypeDict = {
    {"", CommandType::Empty},        {"push", CommandType::Push},
    {"pop", CommandType::Pop},       {"add", CommandType::Add},
    {"sub", CommandType::Sub},       {"neg", CommandType::Neg},
    {"eq", CommandType::Eq},         {"gt", CommandType::Gt},
    {"lt", CommandType::Lt},         {"and", CommandType::And},
    {"or", CommandType::Or},         {"not", CommandType::Not},
    {"label", CommandType::Label},   {"call", CommandType::Call},
    {"if", CommandType::If},         {"function", CommandType::Function},
    {"return", CommandType::Return}, {"all", CommandType::All},
    {"goto", CommandType::Goto},     {"if-goto", CommandType::If_Goto}};
