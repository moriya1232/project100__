

#include "ShuntingYard.h"
#include "Minus.h"
#include "Mul.h"
#include "Number.h"
#include "Plus.h"
#include "Div.h"

#define MULT '*'
#define DIV '/'
#define MINUS '-'
#define PLUS '+'
#define OP_BRACKET '('
#define CL_BRACKET ')'
#define DOT '.'

#include <math.h>


/*
 * this the constructor of ShuntingYard that get the SymbolTableManager.
 */
ShuntingYard::ShuntingYard(SymbolTableManager* symbolTableManager) {
    this->symbolTableManager = symbolTableManager;
}

/*
 * this function bring precedence to operators
 * its return int that represent the precedence
 * ),( : precedence 0
 * +,- : precedence 1
 * *,/ : precedence 2
 *
 */
int ShuntingYard::precedence(char op) {
    if(op == PLUS|| op == MINUS){
        return 1;
    }
    if(op == MULT || op == DIV){
        return 2;
    }
    return 0;
}
/*
 * this function get a string of numbers as infix and returns an Expression
 * as pre fix, that we can calculate.
 * we have 2 stacks that storage the values(Expression) and the operators
 * we have a flag that help us to calculate a negative Expression.
 */
Expression* ShuntingYard::fromInfixToExp(string infixExpression) {
    // stack to store the Expression.
    stack <Expression*> values;
    // stack to store operators.
    stack <char> ops;
    //flag that symbole that we enter to the values stack a neg number
    int isNeg =1;
    //run over the infix string
    for(unsigned int  i = 0; i < infixExpression.length(); i++){

        // Current exp is a whitespace,skip it.
        if(infixExpression[i] == ' ' || infixExpression[i] == '\n'){
            continue;

        }

            // Current exp is an opening brace, push it to 'ops'
        else if(infixExpression[i] == OP_BRACKET){
            ops.push(infixExpression[i]);
        }

            // Current exp is a number, push it to stack of Expression
        else if(isdigit(infixExpression[i])){
            //turn off the flag
            isNeg = 0;
            //temp
            string val;
            // There may be more than one digits in number,so we continue to read the number
            while(i < infixExpression.length() && (isdigit(infixExpression[i]) ||  (infixExpression[i] ==DOT)))
            {
                val += infixExpression[i];
                i++;
            }
            double result = stod(val);
            i--;
            //we div the number by the num of numbers after the dot
            // val += temp;
            //Expression* num = new Number(val);
            //values.push(new Number(val));
            values.push(new Number(result));
        }

            // Closing brace encountered, solve entire brace.
        else if(infixExpression[i] == CL_BRACKET) {
            //while we didnt finish the stack and we dont saw"("
            while (ops.top() != OP_BRACKET && !ops.empty()){

                /*
                 * we take the right and the left Expression and the operator
                 * and create from them Expression.
                 * */
                Expression *right = values.top();
                values.pop();

                Expression *left = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(createExp(left, right, op));
            }

            //remove the operator '(' from the queue
            ops.pop();

            // if the current char is an operator
        } else if (isOperator(infixExpression[i])) {
            //if its negative operator we put zero at the stack
            if (isNeg){
                Expression* num = new Number(0);
                values.push(num);
            }
            /*
             * While top of 'ops' has same or greater precedence to current
             * token, which is an operator.and we dont have a negative sign.
             * Apply operator on top of 'ops' to top two elements in
             * values stack.
             * */
            while (!ops.empty() && !isNeg && (precedence((infixExpression[i])) <=
                                              precedence(ops.top()))){
                //remove the operator from the queue and put in the stack
                Expression *right = values.top();
                values.pop();

                Expression *left = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(createExp(left, right, op));
            }
            isNeg = 1;
            // add the operator to the stack
            ops.push(infixExpression[i]);
            //if its an var that we need to bring his value from the symbolTableManager
        } else {
            isNeg = 0;
            string varName;
            while (i < infixExpression.length() && !isOperator(infixExpression[i]) &&  infixExpression[i]!= '\n'){
                varName += infixExpression[i];
                i++;
            }
            i--;
            //look for the var values at the map
            double numVar = this->symbolTableManager->getValueFromSymbolTable(varName);
            Expression* var = new Number(numVar);
            values.push(var);
        }
    }

    while (!ops.empty()){
        //remove the operator from the stack of perators and put in the stack of values
        Expression *right = values.top();
        values.pop();

        Expression *left = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(createExp(left, right, op));
    }

    return values.top();
}
/*
 * this function get a right and left Expression and an operator
 * and returns an expression from it.
 */
Expression *ShuntingYard::createExp(Expression *left, Expression *right, char operation) {
    switch (operation) {
        case MULT:
            return new Mul(left, right);
        case DIV:
            return new Div(left, right);
        case PLUS:
            return new Plus(left, right);
        case MINUS:
        default:
            return new Minus(left, right);
    }
}

/*
 * this function return true if the char its got its an opertor,false otherwise
 */
bool ShuntingYard::isOperator(char c) {
    return  (c == PLUS|| c == MINUS|| c == MULT || c == DIV || c == CL_BRACKET || c == OP_BRACKET);
}