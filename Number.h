
#ifndef NUMBER_H
#define NUMBER_H

#include "Expression.h"
/*
 * this class represent a number its heiress from Expression
 */
class Number : public Expression{
    double num;
public:
    Number(double num);
    virtual double calculate();
};


#endif //NUMBER_H