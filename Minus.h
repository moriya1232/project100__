

#ifndef MINUS_H
#define MINUS_H

#include "BinaryExpression.h"
/*
 * this class represent the Minus operation,its heiress from BinaryExpression
 */
class Minus :public BinaryExpression{
public:
    Minus(Expression* left, Expression* right);
    virtual double calculate();
};


#endif //MINUS_H