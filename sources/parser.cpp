#include "../includes/parser.h"
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

Parser::Parser(std::string file) {
    Parser::filename = fs::path(file).filename().string();
    Parser::filename = filename.substr(0, filename.find_last_of("."));
    infile.open(file);
    if (!infile.is_open()) {
        throw std::invalid_argument("Input file doesn't exist");
    }
    // std::cout << line << std::endl;
}

void Parser::close() { infile.close(); }

bool Parser::more() { return infile.good(); }

Command Parser::get_next_command() {
    std::string line;
    std::getline(infile, line);
    // std::cout << "the line in get_next_command" << line << std::endl;
    // ignore comments and empty lines
    while ((line.substr(0, 2) == "//" || line.empty() ||
            (line[line.length() - 1] == '\r' && line.length() <= 1)) &&
           infile.good()) {
        std::getline(infile, line);
    }

    if (line.length() > 1 && line[line.length() - 1] == '\r') {
        line = line.substr(0, line.length() - 1);
    }

    if (line.length() == 0) {
        return Command(CommandType::Empty);
    }
    // if the line contains a command we parse it
    // line.erase(std::remove_if(line.begin(), line.end(), ::isspace),
    // line.end());
    std::stringstream ss(line);
    // std::cout << line << std::endl;
    // if (line.find('label') != std::string::npos){

    // }
    Command cmd;
    std::string word;
    int n = 0;
    while (ss >> word) {
        switch (n) {
        case 0:
            cmd.type = CommandTypeDict[word];
            break;
        case 1:
            cmd.type == CommandType::Label || cmd.type == CommandType::Goto ||
                    cmd.type == CommandType::If_Goto ||
                    cmd.type == CommandType::Function ||
                    cmd.type == CommandType::Call
                ? cmd.label_name = word
                : cmd.mem_seg = word;
            break;
        case 2:
            if (std::all_of(word.begin(), word.end(), ::isdigit))
                cmd.arg = (stoi(word));
            break;
        }
        n++;
    }
    cmd.scope = Parser::filename;
    return cmd;
}
