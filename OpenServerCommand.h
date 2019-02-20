#ifndef OPENSERVERCOMMAND_H
#define OPENSERVERCOMMAND_H

#include "Command.h"
#include "SymbolTableManager.h"
/*
 * this class represent a OpenServerCommand
 * means its responsible to the connection with the server.
 */
class OpenServerCommand : public Command{
    SymbolTableManager* stm;
public:
    OpenServerCommand(SymbolTableManager* stm);
    virtual unsigned int doCommand(vector<string> data,unsigned int index);
};


#endif //OPENSERVERCOMMAND_H