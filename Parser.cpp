#include "Parser.h"
#include "EnterC.h"


/*
 * constructor of parser
 */
Parser::Parser(vector<string> data, SymbolTableManager* stm) {
    this->stm = stm;
    this->expsfCommand = this->initializationMapExp();
    this->data = data;
    this->index = 0;

}
/*
 * The function passes over the main vector.
 * When it encounters a string that represents a command it triggers it.
 */
void Parser::parser() {
    //stand on the cur commend
    index = 0;
    while (index < this->data.size()){
        if(expsfCommand.find(data[index]) != expsfCommand.end()){
            Expression* commandExp = expsfCommand.find(data[index])->second;
            index += commandExp->calculate();
        } else {
            index++;
        }
    }
}

/**
 * The function initializes the command map. For each command, it puts the key on the map representing the
 * name of the command and the value representing the command itself.
 * @return the initialized map
 */
map<string, Expression*> Parser::initializationMapExp() {
    map<string, Expression*> expC;

    expC.insert(make_pair(OPEN_DATA_SERVER,new CommandExpression(new OpenServerCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(CONNECT,new CommandExpression(new ConnectCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(VAR,new CommandExpression(new DefineVarCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(ASSIGNMENT,new CommandExpression(new AssignmentCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(PRINT,new CommandExpression(new PrintCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(SLEEP,new CommandExpression(new SleepCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(IF,new CommandExpression(new IfCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(WHILE, new CommandExpression(new WhileCommand(this->stm), this->data, this->index)));

    expC.insert(make_pair(ENTERC, new CommandExpression(new EnterC(), this->data, this->index)));


    return expC;
}

void Parser::freeMemory() {
    for (map<string,Expression*>::iterator it = this->expsfCommand.begin(); it !=  this->expsfCommand.end();it++){
        delete (*it).second;
    }

}