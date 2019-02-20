#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

using namespace std;
/*
 * this class represent a command
 * for each command there is do command method that excecute the command
 * with the given parameters as interpreter
 */
class Command{
public:
    virtual unsigned int doCommand(vector<string> data,unsigned int index) = 0;
    virtual ~Command(){}

};



#endif //COMMAND_H