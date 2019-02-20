
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include "TCPServer.h"
#define BUFFER_SIZE 1024

/*
 * this is the constructor of the TCPServer.
 */
TCPServer::TCPServer(int port) {
    this->port = port;
    //initialize the socket to -1
    this->serverSocket = -1;
}

/**
 * this function start listening to connection.
 * process will go in sleep mode and will wait for the incoming connection.
 */
void TCPServer::startListenToConnect() {

    //initialize the sockets variables
    struct sockaddr_in serv_addr;

    //First call to socket() function
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    socketCommunication = SocketCommunication();/*this->serverSocket*/

    if (this->serverSocket < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->port);


    /* Now bind the host address using bind() call.*/
    if (bind(this->serverSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(this->serverSocket, 5);
}

/**
 * this function accepts actual connection from the client
 * @return the socket
 */
int TCPServer::acceptConnectionFromClient() {
    int newsockfd, clilen;
    struct sockaddr_in cli_addr;

    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(this->serverSocket, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    //cout << "the flightgear is connected to me" << endl;
    return newsockfd;
}


/**
 * this function reads from the socket until the separator char
 * @param separator the char to stop
 * @return the string from the socket
 */
string TCPServer::readFromServer(char separator) {
    return socketCommunication.readFromSocket(this->serverSocket, separator);
}

/**
 * this function write the string data to the socket
 * @param data the string
 */
void TCPServer::writeToServer(string data) {
    socketCommunication.writeToSocket(this->serverSocket, data);
}

/**
 * this function returns the server socket
 * @return server socket
 */
int TCPServer::getSocket() {
    return this->serverSocket;
}