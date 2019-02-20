#include "ConditionParser.h"
#include "ShuntingYard.h"

#define EQUAL '='
#define LESS '<'
#define GREATER '>'
#define NOT '!'
#define F_CL_BRACKET "}"


/*
 * this function get the right and left expression in some condition and the operator
 * between them,in order to check with him the correctness of the condition.
 * its calculate the both expression,check what is the operator
 * and return Bool variable that represent result of the condition between the both expression.
 *
 */
bool ConditionParser::checkCondition(string leftStr, string op, string rightStr, SymbolTableManager* stm) {
    ShuntingYard shuntingYard(stm);
    Expression *left = shuntingYard.fromInfixToExp(leftStr);
    Expression *right = shuntingYard.fromInfixToExp(rightStr);

    double leftCal = left->calculate();
    double rightCal = right->calculate();

    delete  left;
    delete  right;

    //if the operator is one of ==/!=/<=/>=
    if(op.length() == 2){
        switch (op[0]) {
            case EQUAL:
                return leftCal == rightCal;
            case LESS:
                return leftCal <= rightCal;
            case GREATER:
                return leftCal >= rightCal;
            case NOT:
            default:
                return leftCal != rightCal;
        }
        //if its single operator as </>
    } else {
        switch (op[0]){
            case LESS:
                return leftCal < rightCal;
            case GREATER:
            default:
                return leftCal > rightCal;
        }
    }
}


/*
 * this function create a new vector of strings that include commands
 * that found in some scope of condition or function.
 * when it saw '{' its mean start of new scope,and '{' symbolize the end of scope.
 * we count the number of { and } in order to include al the data in some scope
 * and in the necessary time we will call this fun again for another scope that include in her.
 * the function returns a vector of strings.
 */
vector<string> ConditionParser::createConditionData(vector<string> data, int index) {
    int counter = 1;
    vector<string> conditionData;
    unsigned int i = index;
    //when counter is 0,its mean we finish the scope
    while (counter != 0 && i < data.size()){
        if (data[i] == "{"){
            counter++;
        } else if(data[i] == "}"){
            counter--;
        }
        conditionData.push_back(data[i]);
        i++;
    }
    conditionData.pop_back();
    //return the vector with the data in the scope.
    return conditionData;
}