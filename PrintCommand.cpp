#include <iostream>
#include "PrintCommand.h"
#include "ShuntingYard.h"

using namespace std;

/*
 * this is the constructor of the PrintCommand.
 */
PrintCommand::PrintCommand(SymbolTableManager* stm) {
    this->stm=stm;
}

/**
 * The function checks whether what needs to be printed is a string or mathematical expression
 * with variables and prints it accordingly.
 * @param data the main vector
 * @param index the index of the print command
 * @return How much to move in the main vector to read the next command.
 */
unsigned int PrintCommand::doCommand(vector<string> data, unsigned int index) {
    string str = data[index +1];
    if (str[0] == '\"'){
        str = str.substr(1, str.length()-2);
        cout << str << endl;
    } else {
        ShuntingYard shuntingYard(stm);
        Expression *exp;
        exp = shuntingYard.fromInfixToExp(str);
        cout << exp->calculate() << endl;
        delete exp;
    }
    return 2;
}