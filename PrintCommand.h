#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "Command.h"
#include "SymbolTableManager.h"
/*
 * this class represent a print command .
 * its heiress from command.
 * we can print a string by " blabla"
 * or print value of some parameter by blabla
 */
class PrintCommand: public Command {
    SymbolTableManager* stm;
public:
    PrintCommand(SymbolTableManager* stm);
    virtual unsigned int doCommand(vector<string> data,unsigned int index);

};


#endif //PRINTCOMMAND_H