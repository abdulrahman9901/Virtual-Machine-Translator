#include "../includes/codeWriter.h"
#include "../includes/commands.h"
#include <algorithm>
const char kPathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

codeWriter::codeWriter(string inName, bool is_dir) {
    std::string file_name = inName.substr(0, inName.find_last_of("."));
    outfile.open(file_name + ".asm");
    this->name = file_name;
    t_num = 1;
    f_num = 1;
    in_num = 1;

    if (!outfile.is_open()) {
        throw std::invalid_argument("Can't open output file");
    }
    if (is_dir) {
        for (auto line : codeWriter::bootstrap) {
            outfile << line << std::endl;
        }
        Command cmd(CommandType::Call, "Sys.init");
        codeWriter::WriteFunctionCommands(cmd);
    }
}
void codeWriter::Writer_dispatcher(Command command) {
    switch (command.type) {
    case CommandType::Empty:
        break;
    case CommandType::Add:
    case CommandType::Sub:
    case CommandType::Neg:
    case CommandType::Eq:
    case CommandType::Gt:
    case CommandType::Lt:
    case CommandType::And:
    case CommandType::Or:
    case CommandType::Not:
        WriteArthmetic(command);
        break;
    case CommandType::Push:
    case CommandType::Pop:
        WritePushPop(command);
        break;
    case CommandType::Call:
    case CommandType::Function:
    case CommandType::Return:
        WriteFunctionCommands(command);
        break;
    case CommandType::Label:
    case CommandType::Goto:
    case CommandType::If_Goto:
    case CommandType::If:
        WriteFlowCommands(command);
        break;
    }

    return;
}
void codeWriter::WriteFlowCommands(Command command) {
    outfile << "// " << command.get_key() << " " << command.label_name << " "
            << std::endl;
    switch (command.type) {
    case CommandType::Label:
        outfile << "(" + command.label_name + ")" << std::endl;
        break;
    case CommandType::Goto:
    case CommandType::If_Goto:
        for (auto line : branching_code[command.type]) {
            if (line == "label_placeholder")
                outfile << "@" << command.label_name << std::endl;
            else
                outfile << line << std::endl;
        }
    default:
        break;
    }
}
void codeWriter::WriteArthmetic(Command command) {
    outfile << "// " << command.get_key() << std::endl;
    if (command.type == CommandType::Eq || command.type == CommandType::Gt ||
        command.type == CommandType::Lt) {
    }
    for (auto line : arth_logic_code[command.type]) {

        if (line == "@TRUE")
            outfile << line + to_string(t_num) << endl;
        else if (line == "@FALSE")
            outfile << line + to_string(f_num) << endl;
        else if (line == "@INSP")
            outfile << line + to_string(in_num) << endl;
        else if (line == "(TRUE)")
            outfile << line.substr(0, line.size() - 1) + to_string(t_num++) +
                           ")"
                    << endl;
        else if (line == "(FALSE)")
            outfile << line.substr(0, line.size() - 1) + to_string(f_num++) +
                           ")"
                    << endl;
        else if (line == "(INSP)")
            outfile << line.substr(0, line.size() - 1) + to_string(in_num++) +
                           ")"
                    << endl;
        else
            outfile << line << endl;
    }
}
void codeWriter::WritePushPop(Command command) {
    auto type = command.type;
    auto mem_seg = command.mem_seg;
    auto arg = command.arg;
    outfile << "// " << command.get_key() << " " << mem_seg << " "
            << to_string(arg) << std::endl;
    std::string static_var = name.substr(name.find_last_of(kPathSeparator) + 1);

    if (mem_seg == "constant") {
        std::string line = "@" + to_string(arg);
        outfile << line << endl;
    }

    if (type == CommandType::Push) {
        if (mem_seg == "static") {
            std::string line =
                "@" + static_var + "_" + command.scope + "." + to_string(arg);
            outfile << line << endl;
        }
        for (auto count = 0; count < push_codes[mem_seg].size(); count++) {
            if (count == 2 && mem_seg != "static" && mem_seg != "constant") {

                std::string s = "@" + to_string(arg);
                outfile << s << endl;
            }

            outfile << push_codes[mem_seg].at(count) << endl;
        }
    } else {
        for (auto count = 0; count < pop_codes[mem_seg].size(); count++) {
            if (mem_seg == "static") {
                if (count == 3) {
                    std::string line = "@" + static_var + "_" + command.scope +
                                       +"." + to_string(arg);
                    outfile << line << endl;
                }
            } else {
                if (count == 2) {
                    std::string s = "@" + to_string(arg);
                    outfile << s << endl;
                }
            }
            outfile << pop_codes[mem_seg].at(count) << endl;
        }
    }
}
void codeWriter::WriteFunctionCommands(Command command) {
    switch (command.type) {
    case CommandType::Function:
        outfile << "// declare " << command.get_key() << " "
                << command.label_name << " " << to_string(command.arg)
                << std::endl;
        for (auto line : func_code[command.type]) {
            if (line == "function_name")
                outfile << "(" << command.label_name << ")" << std::endl;
            else if (line == "(LCL_INIT)")
                outfile << "(" << command.label_name << "_LCL_INIT)"
                        << std::endl;
            else if (line == "@LCL_INIT")
                outfile << "@" << command.label_name << "_LCL_INIT"
                        << std::endl;
            else if (line == "(NO_ARGS)")
                outfile << "(" << command.label_name << "_NO_ARGS)"
                        << std::endl;
            else if (line == "@NO_ARGS")
                outfile << "@" << command.label_name << "_NO_ARGS" << std::endl;
            else if (line == "K") {
                outfile << "@" << command.arg << std::endl;
            } else
                outfile << line << std::endl;
        }
        break;
    case CommandType::Call:
        outfile << "// " << command.get_key() << " " << command.label_name
                << " " << to_string(command.arg) << std::endl;
        CallStack[command.label_name] += 1;
        for (auto line : func_code[command.type]) {
            if (line == "function_name")
                outfile << "@" << command.label_name << std::endl;
            else if (line == "return_address")
                outfile << "@" + command.label_name + "_" +
                               to_string(CallStack[command.label_name]) +
                               "_return_address"
                        << std::endl;
            else if (line == "(NO_PARAMS)")
                outfile << "(" << command.label_name << "_NO_PARAMS)"
                        << std::endl;
            else if (line == "@NO_PARAMS")
                outfile << "@" << command.label_name << "_NO_PARAMS"
                        << std::endl;
            else if (line == "N")
                outfile << "@" << command.arg << std::endl;
            else
                outfile << line << std::endl;
        }
        outfile << "(" + command.label_name + "_" +
                       to_string(CallStack[command.label_name]) +
                       "_return_address)"
                << std::endl;
        break;
    case CommandType::Return:
        outfile << "// " << command.get_key() << " from function " << std::endl;
        for (auto line : func_code[command.type]) {
            outfile << line << std::endl;
        }
        break;
        break;
    default:
        break;
    }
}
void codeWriter::close() {
    // outfile << "(END)" << std::endl;
    // outfile << "@END" << std::endl;
    // outfile << "0;JMP" << std::endl;
    outfile.close();
}
