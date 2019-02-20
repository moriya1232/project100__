

#ifndef PROJECT1_MY_SHUNTINGYARD_H
#define PROJECT1_MY_SHUNTINGYARD_H

#include <string>
#include "Expression.h"
#include <bits/stdc++.h>
#include "SymbolTableManager.h"
/*
 * this class represent the object ShuntingYard-that is an algoritem of Dijkstra
 * the algoritem get a string as infix its orgenize in queue as postfix.
 * and in reverse reading of the queue We will know the expression we must
 * calculate as prefix
 */
using namespace std;
class ShuntingYard {
    SymbolTableManager* symbolTableManager;

public:
    ShuntingYard(SymbolTableManager* symbolTableManager);
    Expression* fromInfixToExp(string infixExpression);

private:
    int precedence(char op);
    Expression* createExp(Expression *left, Expression *right, char operation);
    bool isOperator(char c);

};


#endif //PROJECT1_MY_SHUNTINGYARD_H