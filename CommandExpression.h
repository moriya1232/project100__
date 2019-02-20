
#ifndef COMMANDEXPRESSION_H
#define COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"
#include "SymbolTableManager.h"


/*
 * this class represent CommandExpression,its heiress from Expression.
 */
class CommandExpression: public Expression {
    Command*  command;
    vector<string> &data;
    unsigned int &index;


public:
    CommandExpression(Command* command,vector<string>& data, unsigned int &index);
    virtual double calculate();

    virtual ~CommandExpression(){
        delete command;
    }

};


#endif //COMMANDEXPRESSION_H