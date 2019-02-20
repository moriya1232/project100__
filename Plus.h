
#ifndef PLUS_H
#define PLUS_H

#include "BinaryExpression.h"
/*
 * this class represent the Plus operation,its heiress from BinaryExpression
 */
class Plus: public BinaryExpression {
public:
    Plus(Expression* left, Expression* right);
    virtual double calculate();

};


#endif