#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include "SocketCommunication.h"
#define BUFFER_SIZE 1024


/*
 * this is the constructor of the SocketCommunication.
 */
SocketCommunication::SocketCommunication() {
}

/**
 * The function read from the given socket until the given separator and returns what it reads.
 * @param socket the socket to read from
 * @param separator read until the separator
 * @return what the function read from the socket
 */
string SocketCommunication::readFromSocket(int socket, char separator) {
    char c = '\0';
    int n;
    string data;

    if (socket < 0){
        perror("ERROR socket not found");
    }

    n = read(socket, &c, 1);
    while (c != separator) {
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        data += c;
        n = read(socket, &c, 1);
    }

    return data;
}

/**
 * The function write the string data to the the given socket.
 * @param socket the socket to write to
 * @param data the string to write
 */
void SocketCommunication::writeToSocket(int socket, string data) {
    int n;
    char buffer[BUFFER_SIZE];
    bzero(buffer,BUFFER_SIZE);
    strcpy(buffer, data.c_str());

    /* Send message to the server */
    n = write(socket, buffer, strlen(buffer));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}