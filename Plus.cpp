
#include "Plus.h"
/*
 * this is the constructor of Plus .
 * its the constructor of the BinaryExpression that Plus heiress from her
 * so we send the :Expression *left and Expression *right to BinaryExpression
 * constructor.
 */
Plus::Plus(Expression *left, Expression *right) :BinaryExpression(left, right){

}
/*
 * this method take the left Expression and calculate him ,take the left
 * Expression and calculate him . and make the operation "+" between them
 */
double Plus::calculate() {
    return this->getLeftExpression()->calculate() + this->getRightExpression()->calculate();
}