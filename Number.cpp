
#include "Number.h"

// constructor
Number::Number(double num) {
    this->num = num;
}

/**
 * this function return the value of this number.
 * @return the number value
 */
double Number::calculate() {
    return this->num;
}