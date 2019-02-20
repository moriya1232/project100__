
#include "Mul.h"
/*
 * this is the constructor of Mul .
 * its the constructor of the BinaryExpression that Mul heiress from her
 * so we send the :Expression *left and Expression *right to BinaryExpression
 * constructor.
 */
Mul::Mul(Expression *left, Expression *right) : BinaryExpression(left, right){

}
/*
 * this method take the left Expression and calculate him ,take the left
 * Expression and calculate him . and make the operation "*" between them
 */
double Mul::calculate() {
    return this->getLeftExpression()->calculate() * this->getRightExpression()->calculate();
}