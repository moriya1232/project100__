#ifndef PARSER_H
#define PARSER_H

#include "Command.h"
#include "Expression.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "SleepCommand.h"
#include "CommandExpression.h"
#include "AssignmentCommand.h"
#include "ConditionParser.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "PrintCommand.h"
#include <vector>
#include <string>
#include <map>
#define OPEN_DATA_SERVER "openDataServer"
#define CONNECT "connect"
#define  ASSIGNMENT "="
#define VAR "var"
#define WHILE "while"
#define PRINT "print"
#define IF "if"
#define SLEEP "sleep"
#define ENTERC "Enterc"


using  namespace std;
/*
 * this class represent a parser that execute commands .
 * the class have vector of string that includes the commands and there parameters
 */
class Parser {
    map<string, Expression*> expsfCommand;
    vector<string> data;
    unsigned int index;
    SymbolTableManager* stm;

public:
    Parser(vector<string> data,SymbolTableManager* stm);
    void parser();
    ~Parser(){
        freeMemory();
    }

    void freeMemory();

private:
    map<string, Expression*> initializationMapExp();
};



#endif //PARSER_H