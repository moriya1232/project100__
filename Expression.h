#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

using namespace std;

/*
 *this is an abstract class that represent Expression.
 *for each Expression there is a method calculate-its calculate the Expression
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression()= default;
};

#endif