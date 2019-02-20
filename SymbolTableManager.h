#ifndef SYMBOLTABLEMANAGER_H
#define SYMBOLTABLEMANAGER_H

#include <string>
#include <mutex>
#include <map>
#include <vector>
#include <set>
#include "TCPClient.h"
#include "TCPServer.h"

#define PATHS_AMOUNT 23

using namespace std;
/*
 * this class represent a SymbolTableManager
 * its include all the vars that live in the program
 * and path in the xml.
 * the class have maps the update during the progrm
 */
class SymbolTableManager {
    mutable mutex m;
    map<string, double> symbolTable;
    map<string, int> fromPathToIndex;
    double flightGearValues[PATHS_AMOUNT];
    map<string, set<string>> dependencyMap;
    TCPClient* client;
    TCPServer server;

public:
    SymbolTableManager();
    double getValueOfPathOrVar(string prm);
    void addVarToSymbolTable(string name, double value);
    double getValueFromSymbolTable(string name);
    void setValuesFromFlightGear(vector<string> values);
    void updateValueAndDependentOn(string prm1, double value);
    void createDependency(string prm1, string prm2);
    void setClient(TCPClient* client);
    void setServer(TCPServer server);
    void closeSockets();
    ~SymbolTableManager(){
        delete this->client;
    }

private:
    void setVarOrPath(string prm1, double value);
    void setVarAtSymbolTable(string name, double value);
    void setValueOfFlightGear(string path, double value);
    void initializationArrayToZero();
    map<string, int> initPathsToIndex();
};


#endif //SYMBOLTABLEMANAGER_H