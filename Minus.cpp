#include "Minus.h"
/*
 * this is the constructor of Minus .
 * its the constructor of the BinaryExpression that Minus heiress from her
 * so we send the :Expression *left and Expression *right to BinaryExpression
 * constructor.
 */
Minus::Minus(Expression *left, Expression *right) : BinaryExpression(left, right){

}
/*
 * this method take the left Expression and calculate him ,take the left
 * Expression and calculate him . and make the operation "-" between them
 */
double Minus::calculate() {
    return this->getLeftExpression()->calculate() - this->getRightExpression()->calculate();
}