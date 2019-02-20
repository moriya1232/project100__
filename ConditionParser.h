

#ifndef CONDITIONPARSER_H
#define CONDITIONPARSER_H

#include "Command.h"
#include "Expression.h"
#include "list"
#include "SymbolTableManager.h"

using namespace std;
/*
 * this class represent a condition parser that heiress from command
 * the condition parser class have right and left expression.
 * in order to check some condition we need values to check it on them
 */
class ConditionParser : public Command{
protected:
    Expression* right;
    Expression* left;

    virtual bool checkCondition(string leftStr, string op, string rightStr, SymbolTableManager* stm);
    virtual vector<string> createConditionData (vector<string> data, int index);

public:
    virtual unsigned int doCommand(vector<string> data, unsigned int index) = 0;
};


#endif //CONDITIONPARSER_H