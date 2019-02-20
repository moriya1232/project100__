#include <math.h>
#include "SymbolTableManager.h"
#include "Expression.h"
#include "ShuntingYard.h"
#include "SocketCommunication.h"

#include <unistd.h>


#define DOT '.'

using namespace std;


SymbolTableManager::SymbolTableManager() {
    initializationArrayToZero();
    this->fromPathToIndex = initPathsToIndex();
    this->client = nullptr;
}

/**
 * The function adds a variable to the symbol table with the given value.
 * @param name a var
 * @param value the value of the var
 */
void SymbolTableManager::addVarToSymbolTable(string name, double value) {
    set<string> vars;
    vars.insert(name);
    //unique_lock<mutex> ul9(m);
    this->symbolTable.insert(make_pair(name, value));
    dependencyMap.insert(make_pair(name, vars));
    //ul9.unlock();

}

/**
 * The function updates the given  value to the  given variable on the symbol table.
 * @param name the var
 * @param value the value
 */
void SymbolTableManager::setVarAtSymbolTable(string name, double value) {
    if (this->symbolTable.find(name) == this->symbolTable.end()){
        throw "this var does not have declaration";
    }
    unique_lock<mutex> ul(m);
    this->symbolTable.find(name)->second = value;
    ul.unlock();
}

/**
 * The function returns the current value of a given var.
 * @param name the var
 * @return the value of the var
 */
double SymbolTableManager::getValueFromSymbolTable(string name) {
    if(this->symbolTable.find(name) != this->symbolTable.end()){
        unique_lock<mutex> ul(m);
        double result = this->symbolTable.find(name)->second;
        ul.unlock();
        return result;
    }
    throw "var not found";
}

/**
 * The function initializes the array of the values ​​from the flight gear to zero.
 */
void SymbolTableManager::initializationArrayToZero() {
    //unique_lock<mutex> ul1(m);
    for(int i = 0; i < PATHS_AMOUNT; i++){
        this->flightGearValues[i] = 0;
    }
    //ul1.unlock();
}

/**
 * The function initializes map and gives each path the appropriate index in the array so that
 * if we search for any path we will know exactly which index in the array to find its value.
 * In addition, the function puts each path in the dependency map with a set that contains itself.
 * @return a initialized map with path and index
 */
map<string, int> SymbolTableManager::initPathsToIndex() {
    map<string, int> pathAndIndex;

    pathAndIndex.insert(make_pair("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    pathAndIndex.insert(make_pair("/instrumentation/altimeter/indicated-altitude-ft", 1));
    pathAndIndex.insert(make_pair("/instrumentation/altimeter/pressure-alt-ft", 2));
    pathAndIndex.insert(make_pair("/instrumentation/attitude-indicator/indicated-pitch-deg", 3));
    pathAndIndex.insert(make_pair("/instrumentation/attitude-indicator/indicated-roll-deg", 4));
    pathAndIndex.insert(make_pair("/instrumentation/attitude-indicator/internal-pitch-deg", 5));
    pathAndIndex.insert(make_pair("/instrumentation/attitude-indicator/internal-roll-deg", 6));
    pathAndIndex.insert(make_pair("/instrumentation/encoder/indicated-altitude-ft", 7));
    pathAndIndex.insert(make_pair("/instrumentation/encoder/pressure-alt-ft", 8));
    pathAndIndex.insert(make_pair("/instrumentation/gps/indicated-altitude-ft", 9));
    pathAndIndex.insert(make_pair("/instrumentation/gps/indicated-ground-speed-kt", 10));
    pathAndIndex.insert(make_pair("/instrumentation/gps/indicated-vertical-speed", 11));
    pathAndIndex.insert(make_pair("/instrumentation/heading-indicator/indicated-heading-deg", 12));
    pathAndIndex.insert(make_pair("/instrumentation/magnetic-compass/indicated-heading-deg", 13));
    pathAndIndex.insert(make_pair("/instrumentation/slip-skid-ball/indicated-slip-skid", 14));
    pathAndIndex.insert(make_pair("/instrumentation/turn-indicator/indicated-turn-rate", 15));
    pathAndIndex.insert(make_pair("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 16));
    pathAndIndex.insert(make_pair("/controls/flight/aileron", 17));
    pathAndIndex.insert(make_pair("/controls/flight/elevator", 18));
    pathAndIndex.insert(make_pair("/controls/flight/rudder", 19));
    pathAndIndex.insert(make_pair("/controls/flight/flaps", 20));
    pathAndIndex.insert(make_pair("/controls/engines/current-engine/throttle", 21));
    pathAndIndex.insert(make_pair("/engines/engine/rpm", 22));

    //unique_lock<mutex> ul7(m);

    for(map<string,int>::iterator it = pathAndIndex.begin(); it != pathAndIndex.end(); ++it){
        set<string> vars;
        vars.insert(it->first);
        dependencyMap.insert(make_pair(it->first, vars));
    }
    //ul7.unlock();
    return pathAndIndex;
}


/**
 * this function set the TCPClient member
 * @param client the TCPClient
 */
void SymbolTableManager::setClient(TCPClient* client) {
    this->client = client;
}

/**
 * this function set the TCPServer member
 * @param server the TCPServer
 */
void SymbolTableManager::setServer(TCPServer server) {
    this->server = server;
}


/**
 * The function accepts the values ​​from the simulator, puts these values ​​in
 * the value array, and updates the variables that depend on the path.
 * @param values the vector with the values
 */
void SymbolTableManager::setValuesFromFlightGear(vector<string> values) {
    ShuntingYard sy(this);
    for (int i = 0; i < PATHS_AMOUNT; i++){
        Expression* result = sy.fromInfixToExp(values[i]);
        unique_lock<mutex> ul2(m);
        this->flightGearValues[i] = result->calculate();
        ul2.unlock();
        delete result;
    }
    for (map<string,int>::iterator it = this->fromPathToIndex.begin(); it != this->fromPathToIndex.end(); ++it){
        unique_lock<mutex> ul2(m);
        int index = it->second;
        double value = this->flightGearValues[index];
        ul2.unlock();
        updateValueAndDependentOn(it->first,value);
    }
}

/**
 * The function accepts a string and checks whether it is a path or a variable and accordingly returns the value.
 * @param prm var or path
 * @return his value
 */
double SymbolTableManager::getValueOfPathOrVar(string prm) {
    double value;
    if (this->fromPathToIndex.find(prm) != this->fromPathToIndex.end()) {
        unique_lock<mutex> ul4(m);
        int index = fromPathToIndex.at(prm);
        value = flightGearValues[index];
        ul4.unlock();
    } else {
        ShuntingYard sy(this);
        Expression* exp = sy.fromInfixToExp(prm);
        value = exp->calculate();
        delete exp;
    }
    return value;
}

/**
 * The function accepts a variable or a path and accordingly updates its value with the given value.
 * @param prm1 var or path
 * @param value the value to update
 */
void SymbolTableManager::setVarOrPath(string prm1, double value) {
    if (prm1[0] == '/') {
        setValueOfFlightGear(prm1, value);
    } else {
        setVarAtSymbolTable(prm1, value);
    }
}

/**
 * The function accepts a variable or a path and accordingly updates its value
 * with the given value and also updates all dependent variables.
 * @param prm1 the var
 * @param value the value to update
 */
void SymbolTableManager::updateValueAndDependentOn(string prm1, double value) {
    //if the parm1 does not found at dependencyMap
    //todo
    if(dependencyMap.find(prm1)== dependencyMap.end()) {
        set<string> set1;
        //insert him to the set
        set1.insert(prm1);
        dependencyMap.insert(make_pair(prm1, set1));
    }
    for(string s: dependencyMap.at(prm1)){
        // if path from server dont update.
        if (prm1 == s && this->fromPathToIndex.find(prm1) != this->fromPathToIndex.end()){
            continue;
        }

        this->setVarOrPath(s, value);
    }
}

/**
 * The function implements the bind command. It creates a dependency between two parameters.
 * After the two parameters will behave as the same variable.
 * In addition, the function update the new value to the first parameter.
 * @param prm1 first parameter
 * @param prm2 second parameter
 */
void SymbolTableManager::createDependency(string prm1, string prm2) {
    set<string> mainSet;
    bool wasInDependencyMay= true;

    //if the parm1 is not found at the dependency map insert him with himself
    if (dependencyMap.find(prm1) == dependencyMap.end()){

        set<string> set1;
        //insert him to the set
        set1.insert(prm1);
        dependencyMap.insert(make_pair(prm1, set1));
    }
    //if the second parm is not at the dependency map we insert him because we saw "bind"
    if(dependencyMap.find(prm2) == dependencyMap.end()) {
        set<string> set2;
        wasInDependencyMay= false;
        //insert him to the set
        set2.insert(prm2);
        dependencyMap.insert(make_pair(prm2, set2));
    }

    //run over the dependency map and enther parameters that depend on it to the main set
    for (string s: dependencyMap.find(prm1)->second) {
        mainSet.insert(s);
    }
    //run over the dependency map and enther parameters that depend on it to the main set
    for (string s: dependencyMap.find(prm2)->second) {
        mainSet.insert(s);
    }
    /*
     * if in xml  or var we take his value and
     * 1.put for every depend parameters the value
     * 2.initilize the set of every depend parameter to the main set
     */
    if(wasInDependencyMay) {
        double value = getValueOfPathOrVar(prm2);
        for (string s: mainSet) {
            setVarOrPath(s, value);
            if (dependencyMap.find(s) != dependencyMap.end()) {
                unique_lock<mutex> ul5(m);
                dependencyMap.find(s)->second = mainSet;
                ul5.unlock();
            }
        }
        /*
        * if not in xml  or var we take his value and
        * 1.put for every depend parameters the value
        * 2.initilize the set of every depend parameter to the main set
        */
    }else {
        for (string s: mainSet) {
            if (dependencyMap.find(s) != dependencyMap.end()) {
                unique_lock<mutex> ul6(m);
                dependencyMap.find(s)->second = mainSet;
                ul6.unlock();
            }
        }
    }
}

/**
 * The function sends to the simulator a new value to a specific path and updates it.
 * @param path  the path to change
 * @param value the new value
 */
void SymbolTableManager::setValueOfFlightGear(string path, double value) {
    if (this->client == nullptr){
        return;
    }

    if (this->client->getSocket() != -1){
        string data = "set "+ path + ' ' + to_string(value) + "\r\n" ;
        this->client->writeToServer(data);
    }
}

void SymbolTableManager::closeSockets() {

    if (this->client != nullptr){
        close(this->client->getSocket());
    }
    close(this->server.getSocket());

}