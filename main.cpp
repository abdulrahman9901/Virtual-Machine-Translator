#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "./includes/codeWriter.h"
#include "./includes/commands.h"
#include "./includes/parser.h"

const char kPathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

using namespace std;

namespace fs = std::filesystem;

Parser* parser;
// https://stackoverflow.com/questions/11140483/how-to-get-list-of-files-with-a-specific-extension-in-a-given-folder
std::vector<std::string> get_all(fs::path const& root, std::string const& ext) {
    std::vector<std::string> paths{root.string() + kPathSeparator + "Sys.vm"};

    if (fs::exists(root) && fs::is_directory(root)) {
        for (auto const& entry : fs::recursive_directory_iterator(root)) {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext)
                if (entry.path().filename() != "Sys.vm")
                    paths.emplace_back(entry.path().string());
        }
    }

    return paths;
}

codeWriter* writer;
/// @brief main Vm translator loop
/// @param argc number of arguments=1
/// @param argv name and path of the file
/// @return 0
int main(int argc, char** argv) {

    if (argc < 2) {
        cout << "Not enough arguments" << endl;
        return 1;
    }
    std::vector<std::string> infiles;
    std::string outfile;
    if (fs::is_directory(fs::status(argv[1]))) {
        fs::path root = argv[1];
        outfile = argv[1];
        outfile += kPathSeparator;
        outfile += root.filename().string();
        outfile += ".asm";
        std::cout << "out file is " << outfile << std::endl;
        std::string ext = ".vm";
        infiles = get_all(root, ext);
        for (std::string p : infiles) {
            std::cout << p << std::endl;
        }
    } else if (fs::is_regular_file(fs::status(argv[1]))) {
        // getting the input file name and path from input arguments
        infiles = {argv[1]};
        // generating output file name with same name and path but with .asm
        // extension
        int dotPos = infiles[0].rfind(".");
        outfile = infiles[0].substr(0, dotPos);
        outfile += ".asm";
    } else {
        std::cerr << "something wrong with the input filename or directory "
                  << std::endl;
        return 0;
    }

    // initialize codeWriter
    try {
        writer = new codeWriter(outfile, fs::is_directory(fs::status(argv[1])));
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
        return 0;
    }

    for (std::string infile : infiles) {
        // initialize parser
        try {
            parser = new Parser(infile);
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
            return 0;
        }
        // loop through all the lines in the file parser them and extract
        // commands then write corresponding assembly commands.
        while (parser->more()) {
            Command cmd = parser->get_next_command();
            // std::cout << "In main loop : " << cmd.get_key() << std::endl;
            writer->Writer_dispatcher(cmd);
        }
        parser->close();
    }
    writer->close();
    return 0;
}