#ifndef PARSER_H
#define PARSER_H

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "commands.h"

class Parser {
  private:
    // private data members
    std::ifstream infile;
    std::string filename;

  public:
    Parser(std::string file);
    void close();
    bool more();
    Command get_next_command();
};
#endif