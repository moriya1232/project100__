
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "SocketCommunication.h"
/*
 * this class represent a TCPServer.
 * it have port ,socket of the server
 * and SocketCommunication in order to be able to connect
 */
class TCPServer{
    int port;
    int serverSocket;
    SocketCommunication socketCommunication;
public:
    TCPServer(){}
    TCPServer(int port);
    void startListenToConnect();
    int acceptConnectionFromClient();
    string readFromServer(char separator);
    void writeToServer(string data);
    int getSocket();
};

#endif //TCPSERVER_Ha