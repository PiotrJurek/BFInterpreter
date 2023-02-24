#include <stack>
#include <string>
#include "../Interpreter/interpreter.h"
#include "compiler.h"

#define START "section .data\n\tbuffer: times 30000 db 0\n\nsection .text\n\tglobal _start\n\n_start:\n\tmov ecx, buffer\n\tmov ebx, 0\n"
#define RIGHT "\tinc ecx\n"
#define LEFT "\tdec ecx\n"
#define PLUS "\tinc byte [ecx]\n"
#define MINUS "\tdec byte [ecx]\n"
#define DOT "\tmov eax, 4\n\tmov ebx, 1\n\tmov ecx, ecx\n\tmov edx, 1\n\tint 0x80\n"
#define COMMA "\tmov eax, 3\n\tmov ebx, 0\n\tmov ecx, ecx\n\tmov edx, 1\n\tint 0x80\n"
#define END "\tmov eax, 1\n\tint 0x80\n"

int compile(const std::string &code, std::string &output, int printWarnings) {
    int error = validate(code, printWarnings);
    if (error) {
        return error;
    }

    output = START;
    int bracketCounter = 0;
    std::stack<int> brackets;

    for (int i = 0; code[i] != '\0'; i++) {
        switch (code[i]) {
            case '>':
                output += RIGHT;
                break;
            case '<':
                output += LEFT;
                break;
            case '+':
                output += PLUS;
                break;
            case '-':
                output += MINUS;
                break;
            case '.':
                output += DOT;
                break;
            case ',':
                output += COMMA;
                break;
            case '[':
                bracketCounter++;
                output += "loop_start_" + std::to_string(bracketCounter) + ":\n\tcmp byte [ecx], 0\n\tje loop_end_" +
                          std::to_string(bracketCounter) + "\n";
                brackets.push(bracketCounter);
                break;
            case ']':
                output += "\tjmp loop_start_" + std::to_string(brackets.top()) + "\nloop_end_" +
                          std::to_string(brackets.top()) + ":\n";
                brackets.pop();
                break;
            default:
                break;
        }
    }

    output += END;
    return 0;
}