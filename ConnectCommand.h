

#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H

#include "Command.h"
#include "SymbolTableManager.h"

/*
 * this class represent a ConnectCommand .
 * the connect have ip and port
 * its responsible to connectection
 */
class ConnectCommand : public Command{
    SymbolTableManager* stm;
public:
    ConnectCommand(SymbolTableManager* stm);
    virtual  unsigned int doCommand(vector<string> data,unsigned int index);
};


#endif //CONNECTCOMMAND_H