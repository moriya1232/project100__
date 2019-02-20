#include "IfCommand.h"
#include "ShuntingYard.h"
#include "Parser.h"
#define FIRST_PRM 1
#define SEC_PRM 2
#define THIRD_PRM 3
#define START_EXCUT 5


/*
 * this is the constructor of the IfCommand.
 */
IfCommand::IfCommand(SymbolTableManager* stm) {
    this->stm = stm;
}

/**
 * The function checks whether the condition exists and if it is true,
 * it executes all the commands within the scope.
 * @param data the main vector
 * @param index the index if the command on the vector
 * @return how mach moves to step after this command.
 */
unsigned int IfCommand::doCommand(vector<string> data, unsigned int index) {
    // take the 2 parameters and the operator
    string leftStr = data[index + FIRST_PRM];
    string op = data[index + SEC_PRM];
    string rightStr = data[index + THIRD_PRM];
    // create vector with the commands in the scope
    vector<string> conditionData = this->createConditionData(data, index + START_EXCUT);
    // execute the commands if the condition is true
    if (this->checkCondition(leftStr, op, rightStr, this->stm)){
        Parser parser(conditionData, this->stm);
        parser.parser();
    }

    return conditionData.size() + START_EXCUT + 1;
}
