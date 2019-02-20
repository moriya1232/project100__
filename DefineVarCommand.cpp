

#include "DefineVarCommand.h"

/*
 * this is the constructor of the DefineVarCommand
 */
DefineVarCommand::DefineVarCommand(SymbolTableManager *stm) {
    this->stm = stm;
}


/**
 * The function creates a variable that is initialized to a value of 0 and adds to the symbol table.
 * @param data the main vector
 * @param index the index if the command on the vector
 * @return how mach moves to step after this command.
 */
unsigned int DefineVarCommand::doCommand(vector<string> data, unsigned int index) {
    string varName = data[index +1];
    this->stm->addVarToSymbolTable(varName, 0);

    return 2;
}