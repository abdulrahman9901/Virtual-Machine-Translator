#ifndef WRITER_H
#define WRITER_H
// page 241
#include "commands.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class codeWriter {
  private:
    ofstream outfile;
    string name;
    int t_num, f_num, in_num;
    map<string, int> CallStack{};
    std::vector<string> bootstrap{"@256", "D=A", "@SP", "M=D"};
    map<CommandType, vector<string>> arth_logic_code{

        {CommandType::Add,
         vector<string>{"@SP", "M=M-1", "A=M", "D=M", "@SP", "M=M-1", "A=M",
                        "M=D+M", "@SP", "M=M+1"}},
        {CommandType::Sub,
         vector<string>{"@SP", "M=M-1", "A=M", "D=M", "@SP", "M=M-1", "A=M",
                        "M=M-D", "@SP", "M=M+1"}},
        {CommandType::Neg,
         vector<string>{"@SP", "M=M-1", "A=M", "M=-M", "@SP", "M=M+1"}},
        {CommandType::Eq,
         vector<string>{"@SP",   "AM=M-1", "D=M",    "@SP",    "AM=M-1",
                        "D=M-D", "@TRUE",  "D;JEQ",  "@SP",    "A=M",
                        "M=0",   "@INSP",  "0;JMP",  "(TRUE)", "@SP",
                        "A=M",   "M=-1",   "(INSP)", "@SP",    "M=M+1"}},
        {CommandType::Gt,
         vector<string>{"@SP",   "AM=M-1", "D=M",    "@SP",    "AM=M-1",
                        "D=M-D", "@TRUE",  "D;JGT",  "@SP",    "A=M",
                        "M=0",   "@INSP",  "0;JMP",  "(TRUE)", "@SP",
                        "A=M",   "M=-1",   "(INSP)", "@SP",    "M=M+1"}},
        {CommandType::Lt,
         vector<string>{"@SP",   "AM=M-1", "D=M",    "@SP",    "AM=M-1",
                        "D=M-D", "@TRUE",  "D;JLT",  "@SP",    "A=M",
                        "M=0",   "@INSP",  "0;JMP",  "(TRUE)", "@SP",
                        "A=M",   "M=-1",   "(INSP)", "@SP",    "M=M+1"}},
        {CommandType::And, vector<string>{"@SP", "AM=M-1", "D=M", "@SP",
                                          "AM=M-1", "M=D&M", "@SP", "M=M+1"}},
        {CommandType::Or, vector<string>{"@SP", "AM=M-1", "D=M", "@SP",
                                         "AM=M-1", "M=D|M", "@SP", "M=M+1"}},
        {CommandType::Not,
         vector<string>{"@SP", "AM=M-1", "M=!M", "@SP", "M=M+1"}}};

    map<string, vector<string>> push_codes{
        {"local", vector<string>{"@LCL", "D = M", "A = A + D", "D=M", "@SP",
                                 "A=M", "M=D", "@SP", "M=M+1"}},
        {"static", vector<string>{"D=M", "@SP", "A=M", "M=D", "@SP", "M=M+1"}},
        {"argument", vector<string>{"@ARG", "D=M", "A=A+D", "D=M", "@SP", "A=M",
                                    "M=D", "@SP", "M=M+1"}},
        {"temp", vector<string>{"@5", "D=A", "A=A+D", "D=M", "@SP", "A=M",
                                "M=D", "@SP", "M=M+1"}},
        {"pointer", vector<string>{"@3", "D=A", "A=A+D", "D=M", "@SP", "A=M",
                                   "M=D", "@SP", "M=M+1"}},
        {"this", vector<string>{"@THIS", "D=M", "A=A+D", "D=M", "@SP", "A=M",
                                "M=D", "@SP", "M=M+1"}},
        {"that", vector<string>{"@THAT", "D=M", "A=A+D", "D=M", "@SP", "A=M",
                                "M=D", "@SP", "M=M+1"}},
        {"constant",
         vector<string>{"D=A", "@SP", "A=M", "M=D", "@SP", "M=M+1"}}};
    map<string, vector<string>> pop_codes{

        {"local", vector<string>{"@LCL", "D= M", "A = A + D", "D=A", "@SP",
                                 "AM=M-1", "D=D+M", "A=D-M", "M=D-A"}},
        {"static", vector<string>{"@SP", "AM=M-1", "D=M", "M=D"}},
        {"argument", vector<string>{"@ARG", "D= M", "A = A + D", "D=A", "@SP",
                                    "AM=M-1", "D=D+M", "A=D-M", "M=D-A"}},
        {"temp", vector<string>{"@5", "D= A", "A = A + D", "D=A", "@SP",
                                "AM=M-1", "D=D+M", "A=D-M", "M=D-A"}},
        {"pointer", vector<string>{"@3", "D= A", "A = A + D", "D=A", "@SP",
                                   "AM=M-1", "D=D+M", "A=D-M", "M=D-A"}},
        {"this", vector<string>{"@THIS", "D= M", "A = A + D", "D=A", "@SP",
                                "AM=M-1", "D=D+M", "A=D-M", "M=D-A"}},
        {"that", vector<string>{"@THAT", "D= M", "A = A + D", "D=A", "@SP",
                                "AM=M-1", "D=D+M", "A=D-M", "M=D-A"}},
    };
    map<CommandType, vector<string>> branching_code{
        {CommandType::Goto, vector<string>{"label_placeholder", "0;JMP"}},
        {CommandType::If_Goto,
         vector<string>{"@SP", "AM=M-1", "D=M", "label_placeholder", "D;JNE"}}};
    map<CommandType, vector<string>> func_code{
        {CommandType::Function, vector<string>{"function_name",
                                               "@0",
                                               "D=A",
                                               "@R10",
                                               "M=D",
                                               "K",
                                               "D=A",
                                               "@R12",
                                               "M=D",
                                               "@NO_ARGS",
                                               "D;JEQ",
                                               "(LCL_INIT)",
                                               "@R10",
                                               "D=M",
                                               "@SP",
                                               "A=M+D",
                                               "M=0",
                                               "@R10",
                                               "M=M+1",
                                               "D=M",
                                               "@R12",
                                               "D=M-D",
                                               "@LCL_INIT",
                                               "D;JGT",
                                               "K",
                                               "D=A",
                                               "@SP",
                                               "M=M+D",
                                               "(NO_ARGS)"}},
        {CommandType::Return,
         vector<string>{
             "@LCL", "D=M",   "@R11", "M=D", "@5",    "D=A",    "@R11", "D=M-D",
             "A=D",  "D=M",   "@R9",  "M=D", "@SP",   "AM=M-1", "D=M",  "@ARG",
             "A=M",  "M=D",   "@ARG", "D=M", "@SP",   "M=D+1",  "@R11", "D=M",
             "@1",   "D=D-A", "A=D",  "D=M", "@THAT", "M=D",    "@R11", "D=M",
             "@2",   "D=D-A", "A=D",  "D=M", "@THIS", "M=D",    "@R11", "D=M",
             "@3",   "D=D-A", "A=D",  "D=M", "@ARG",  "M=D",    "@R11", "D=M",
             "@4",   "D=D-A", "A=D",  "D=M", "@LCL",  "M=D",    "@R9",  "A=M",
             "0;JMP"}},
        {CommandType::Call, vector<string>{
                                "return_address",
                                "D=A",
                                "@SP",
                                "A=M",
                                "M=D",
                                "@SP",
                                "M=M+1",
                                "@LCL",
                                "D=M",
                                "@SP",
                                "A=M",
                                "M=D",
                                "@SP",
                                "M=M+1",
                                "@ARG",
                                "D=M",
                                "@SP",
                                "A=M",
                                "M=D",
                                "@SP",
                                "M=M+1",
                                "@THIS",
                                "D=M",
                                "@SP",
                                "A=M",
                                "M=D",
                                "@SP",
                                "M=M+1",
                                "@THAT",
                                "D=M",
                                "@SP",
                                "A=M",
                                "M=D",
                                "@SP",
                                "M=M+1",
                                "N",
                                "D=A",
                                "@SP",
                                "D=M-D",
                                "@5",
                                "D=D-A",
                                "@ARG",
                                "M=D",
                                "@SP",
                                "D=M",
                                "@LCL",
                                "M=D",
                                "function_name",
                                "0;JMP",
                            }}};

  public:
    codeWriter(string inName, bool is_dir);
    void WriteFlowCommands(Command command);
    void WriteFunctionCommands(Command command);
    void Writer_dispatcher(Command command);
    void WriteArthmetic(Command command);
    void WritePushPop(Command command);
    void close();
};
#endif