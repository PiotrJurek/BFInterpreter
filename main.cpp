#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Interpreter/interpreter.h"

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "ERROR: No file name entered.";
        return 1;
    }

    int printWarnings = 0;
    if (argc == 3) {
        if (strcmp(argv[2], "-Warn") == 0) {
            printWarnings = 1;
        } else {
            std::cout << "ERROR: Entered not existing argument.";
            return 2;
        }
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "ERROR: File with the specified name does not exist.";
        return 1;
    }

    std::stringstream fileContent;
    fileContent << file.rdbuf();
    std::string code = fileContent.str();
    file.close();


    int error = interpret(code, printWarnings);
    if (error) {
        return error;
    }

    return 0;
}