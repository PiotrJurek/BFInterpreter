#ifndef BFINTERPRETER_INTERPRETER_H
#define BFINTERPRETER_INTERPRETER_H

#include <iostream>

int validate(const std::string& code, int printWarnings);

int interpret(const std::string& code, int printWarnings);

#endif //BFINTERPRETER_INTERPRETER_H
