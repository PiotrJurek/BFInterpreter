#include <iostream>
#include "interpreter.h"

int validate(const std::string &code, int printWarnings) {
    int pointer = 0;
    int bracketCounter = 0;

    for (int i = 0; code[i] != '\0'; i++) {
        switch (code[i]) {
            case '>':
                pointer++;
                if (printWarnings && pointer >= 30000) {
                    std::cout << "WARNING: Pointer outside of scope on char " << i + 1 << "\n";
                }
                break;
            case '<':
                pointer--;
                if (printWarnings && pointer < 0) {
                    std::cout << "WARNING: Pointer outside of scope on char " << i + 1 << "\n";
                }
                break;
            case '+':
            case '-':
            case ',':
                if (pointer < 0 || pointer >= 30000) {
                    std::cout << "ERROR: Writing outside of scope on char " << i + 1 << "\n";
                    return 2;
                }
                break;
            case '.':
                if (pointer < 0 || pointer >= 30000) {
                    std::cout << "ERROR: Reading outside of scope on char " << i + 1 << "\n";
                    return 2;
                }
                break;
            case '[':
                bracketCounter++;
                if (code[i + 1] == ']') {
                    std::cout << "ERROR: Infinite loop on char " << i + 1 << "\n";
                    return 2;
                }
                break;
            case ']':
                bracketCounter--;
                if (bracketCounter < 0) {
                    std::cout << "ERROR: ']' without corresponding '[' on char " << i + 1 << "\n";
                    return 2;
                }
                break;
            default:
                break;
        }
    }

    if (bracketCounter != 0) {
        std::cout << "ERROR: Unclosed '[' at end of file\n";
        return 2;
    }

    return 0;
}


int interpret(const std::string &code, int printWarnings) {
    int error = validate(code, printWarnings);
    if (error) {
        return error;
    }

    char bytes[30000] = {0};
    char *pointer = bytes;
    int bracketCounter = 0;

    for (int i = 0; code[i] != '\0'; i++) {
        switch (code[i]) {
            case '>':
                pointer++;
                break;
            case '<':
                pointer--;
                break;
            case '+':
                (*pointer)++;
                break;
            case '-':
                (*pointer)--;
                break;
            case '.':
                std::cout << *pointer;
                break;
            case ',':
                std::cin >> *pointer;
                break;
            case '[':
                bracketCounter++;
                if (*pointer == 0) {
                    int endBracketCounter = bracketCounter - 1;
                    do {
                        i++;
                        if (code[i] == '[') bracketCounter++;
                        else if (code[i] == ']') bracketCounter--;
                    } while (bracketCounter != endBracketCounter);
                }
                break;
            case ']':
                bracketCounter--;
                if (*pointer != 0) {
                    int endBracketCounter = bracketCounter + 1;
                    do {
                        i--;
                        if (code[i] == '[') bracketCounter++;
                        else if (code[i] == ']') bracketCounter--;
                    } while (bracketCounter != endBracketCounter);
                }
                break;
            default:
                break;
        }
    }

    return 0;
}