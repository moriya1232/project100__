

#ifndef DATAREADERSERVER_H
#define DATAREADERSERVER_H


#include "TCPServer.h"
#include "SymbolTableManager.h"
#include <vector>
/*
 * this class represent DataReaderServer
 * the class charge to accept the connection and read the data frm the server
 */
class DataReaderServer {
    TCPServer server;
    int rate;
public:
    DataReaderServer(int port, int rate);
    void acceptConnectionsAndReadData(SymbolTableManager *stm);

};

vector<string> split(const string& str, char delimiter);

#endif //DATAREADERSERVER_H