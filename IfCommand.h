#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "ConditionParser.h"
#include "SymbolTableManager.h"
/*
* this class represent if command its heiress from ConditionParser
 * the if command is a if condition that if the condition is true
 * the commands are in the scope are execute.
 * this class containing a  SymbolTableManager in order to achieve the values of parameters
 * in the program.
 */
class IfCommand : public ConditionParser{
    SymbolTableManager* stm;
public:
    IfCommand(SymbolTableManager* stm);
    virtual unsigned int doCommand(vector<string> data, unsigned int index);
};


#endif //IFCOMMAND_H