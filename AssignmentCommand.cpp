
#include "AssignmentCommand.h"
#include "Expression.h"
#include "ShuntingYard.h"
#define BIND "bind"

using namespace std;
/*
* this is the constructor of  AssignmentCommand
*/
AssignmentCommand::AssignmentCommand(SymbolTableManager *stm) {
    this->stm = stm;
}

/*
 * this function responsible to Assignment
 * we have 2 parameters
 * one before the = operator ,and another after the = operator
 */
unsigned int AssignmentCommand::doCommand(vector<string> data, unsigned int index) {
    int returnValue;
    string prm1 = data[index - 1];

    //if its path we delete the " "
    if (prm1[0] == '\"'){
        prm1 = deleteQuote(prm1);
    }
    //if there is bind between 2 parameters
    if (data[index + 1] == BIND){
        string prm2 = data[index + 2];
        if (prm2[0] == '\"'){
            prm2 = deleteQuote(prm2);
        }
        returnValue = 3;
        this->stm->createDependency(prm1, prm2);
        //if its not path
    } else {
        returnValue = 2;
        string prm2 = data[index + 1];
        if (prm2[0] == '\"'){
            prm2 = deleteQuote(prm2);
        }
        //bring the value of the parm2 from the symbolTable map
        double value = stm->getValueOfPathOrVar(prm2);
        //update the value of the paramethrs which depends this parm1
        stm->updateValueAndDependentOn(prm1, value);
    }

    return returnValue;
}

/*
 * this function delete the " " from string
 */
string AssignmentCommand::deleteQuote(string str) {
    return  str.substr(1, str.length()-2);
}