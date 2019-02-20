
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "SocketCommunication.h"

using namespace std;
/*
 * this class represent a TCPClient.
 * it have port ,socket of the client,and ipAddress
 * and SocketCommunication in order to be able to connect
 */
class TCPClient {
    int clientSocket;
    int port;
    string ipAddress;
    SocketCommunication socketCommunication;
public:
    int getSocket();
    TCPClient(string ipAddress, int port);
    void connectToServer();
    string readFromServer(char separator);
    void writeToServer(string data);
    ~TCPClient(){
    }
};


#endif //TCPCLIENT_H