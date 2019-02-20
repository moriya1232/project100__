
#include "Div.h"
/*
 * this is the constructor of div .
 * its the constructor of the BinaryExpression that div heiress from her
 * so we send the :Expression *left and Expression *right to BinaryExpression
 * constructor.
 */
Div::Div(Expression *left, Expression *right): BinaryExpression(left, right) {

}
/*
 * this method take the left Expression and calculate him ,take the left
 * Expression and calculate him . and make the operation "/" between them
 */
double Div::calculate() {
    return this->getLeftExpression()->calculate() / this->getRightExpression()->calculate();
}