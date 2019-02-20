
#ifndef DEFINEVARCOMMAND_H
#define DEFINEVARCOMMAND_H

#include <map>
#include <vector>
#include "Command.h"
#include "SymbolTableManager.h"

using namespace std;
/*
 * this class represent DefineVarCommand
 * its charge to define a new var in the program
 */
class DefineVarCommand : public Command{
    SymbolTableManager* stm;
public:
    DefineVarCommand(SymbolTableManager* stm);
    virtual unsigned int doCommand(vector<string> data, unsigned int index);

};


#endif //DEFINEVARCOMMAND_H