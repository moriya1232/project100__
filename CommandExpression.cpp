

#include "CommandExpression.h"
/*
 * this is the constructor of the CommandExpression.
 */
CommandExpression::CommandExpression(Command* command, vector<string>& data, unsigned int& index ):
        data(data), index(index){
    this->command = command;

}
/*
 * this method calculate -take the command and turn it on the do command nethod
 */
double CommandExpression::calculate() {
    return this->command->doCommand(this->data, this->index);
}