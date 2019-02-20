

#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"
/*
 * this class represent a binary Expression, its heiress from Expression
 * its also an abstract class .
 * the class composed from 2 Expression. left and right .
 * its have the methods "get left Expression" and "get right Expression"
 * and its also have a distractor.
 *
 */
class BinaryExpression :public Expression{
protected:
    Expression* right;
    Expression* left;
public:
    BinaryExpression(Expression* left, Expression* right);
    virtual double calculate() = 0;
    Expression* getRightExpression();
    Expression* getLeftExpression();
    ~BinaryExpression()override{
        delete this->left;
        delete this->right;
    };
};

#endif