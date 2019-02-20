

#include "BinaryExpression.h"
/*
 * this is the constructor of the BinaryExpression
 */
BinaryExpression::BinaryExpression(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}
/*
 * this method return tha left Expression
 */
Expression* BinaryExpression::getLeftExpression() {
    return this->left;
}
/*
 * this method return tha right Expression
 */
Expression* BinaryExpression::getRightExpression() {
    return this->right;
}
/*
 * distructor of BinaryExpression
 */