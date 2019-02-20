
#ifndef ASSIGNMENTCOMMAND_H
#define ASSIGNMENTCOMMAND_H

#include "Command.h"
#include "SymbolTableManager.h"
/*
 * this class represent AssignmentCommand, this class
 * responsible to Assignment of valuse
 */

class AssignmentCommand: public Command{
    SymbolTableManager* stm;
public:
    AssignmentCommand(SymbolTableManager* stm);
    virtual unsigned int doCommand(vector<string> data, unsigned int index);

private:
    string deleteQuote(string str);
};


#endif //ASSIGNMENTCOMMAND_H