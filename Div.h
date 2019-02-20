#ifndef DIV_H
#define DIV_H

#include "BinaryExpression.h"
/*
 * this class represent the div operation,its heiress from BinaryExpression
 */
class Div :public BinaryExpression{
public:
    Div(Expression* left, Expression* right);
    virtual double calculate();
};


#endif //DIV_H