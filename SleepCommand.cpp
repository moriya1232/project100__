

#include "SleepCommand.h"
#include "Expression.h"
#include "ShuntingYard.h"
#include <unistd.h>
/*
 * this is the constructor of the WhileCommand.
 */
SleepCommand::SleepCommand(SymbolTableManager* stm) {
    this->stm=stm;
}

/**
 * The function suspends the program for milliseconds and returns how
 * mach moves in the main vector to get to the next command.
 * @param data main vector
 * @param index the index of the command
 * @return How much to move in the main vector to read the next command.
 */
unsigned int SleepCommand::doCommand(vector<string> data, unsigned int index) {
    string str = data[index + 1];
    ShuntingYard shuntingYard(stm);
    Expression *milisec = shuntingYard.fromInfixToExp(str);
    usleep(milisec->calculate() * 1000);
    delete milisec;
    return 2;
}