#ifndef SOCKETCOMMUNICATION_H
#define SOCKETCOMMUNICATION_H

#include <string>

using namespace std;
/*
 * this class represent Communication with Socket
 * its have the ability to read and write into Socket.
 */
class SocketCommunication {
public:
    SocketCommunication();
    string readFromSocket(int socket, char separator);
    void writeToSocket(int socket, string data);

};


#endif //SOCKETCOMMUNICATION_H