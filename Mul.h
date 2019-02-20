
#ifndef MUL_H
#define MUL_H

#include "BinaryExpression.h"
/*
 * this class represent the Multiplication operation,
 * its heiress from BinaryExpression
 */
class Mul :public BinaryExpression{

public:
    Mul(Expression* left, Expression* right);
    virtual double calculate();
};


#endif //MUL_H