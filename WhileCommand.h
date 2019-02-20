
#ifndef WHILECOMMAND_H
#define WHILECOMMAND_H

#include "ConditionParser.h"
#include "SymbolTableManager.h"




/*
* this class represent while command its heiress from ConditionParser
 * the while command is a while loop that as much the condition within its exists
 * the commands are in the scope are execute.
 * this class containing a  SymbolTableManager in order to achieve the values of parameters
 * in the program.
 */
class WhileCommand : public ConditionParser{
    SymbolTableManager* stm;
public:
    WhileCommand(SymbolTableManager* stm);
    virtual unsigned int doCommand(vector<string> data, unsigned int index);
};


#endif //WHILECOMMAND_H