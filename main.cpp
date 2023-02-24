#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Interpreter/interpreter.h"
#include "Compiler/compiler.h"

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "ERROR: No file name entered.\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile;
    int printWarnings = 0;

    if (!inputFile.is_open()) {
        std::cout << "ERROR: File with name: " << argv[1] << " does not exist.\n";
        return 1;
    }

    std::stringstream fileContent;
    fileContent << inputFile.rdbuf();
    std::string code = fileContent.str();
    inputFile.close();

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-O") == 0) {
            i++;
            outputFile.open(argv[i]);
            if (!outputFile.is_open()) {
                std::cout << "ERROR: File with name: " << argv[i] << " does not exist.\n";
                return 1;
            }
        } else if (strcmp(argv[i], "-Warn") == 0) {
            printWarnings = 1;
        } else {
            std::cout << "ERROR: Entered not existing argument.\n";
            return 2;
        }
    }

    int error;

    if (!outputFile.is_open()) {
        error = interpret(code, printWarnings);
        if (error) {
            return error;
        }
        return 0;
    }

    std::string output;
    error = compile(code, output, printWarnings);
    if (error) {
        return error;
    }
    outputFile.clear();
    outputFile << output;
    outputFile.close();

    return 0;
}