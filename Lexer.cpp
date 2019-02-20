
#include <fstream>
#include "Lexer.h"
#include <vector>
#define MULT '*'
#define DIV '/'
#define MINUS '-'
#define PLUS '+'
#define EQUAL '='
#define LESS '<'
#define GREATER '>'
#define NOT '!'
#define TAB '\t'
#define COMMA ','
#define SPACE ' '
#define OP_BRACKET '('
#define CL_BRACKET ')'
#define F_OP_BRACKET '{'
#define F_CL_BRACKET '}'
#define GERESH '\"'
#define B_SLASH '\\'
#define GREATER_E ">="
#define LESS_E "<="
#define EQUAL_E "=="
#define NOT_E "!="

#define OPEN_DATA_SERVER "openDataServer"
#define CONNECT "connect"
#define ASSIGNMENT "="
#define VAR "var"
#define WHILE "while"
#define PRINT "print"
#define IF "if"
#define SLEEP "sleep"
#define ENTERC "Enterc"
#define BIND "bind"


/*
 * this is the constructor of the Lexer.
 */
Lexer::Lexer() {

}

/**
 * The function checks whether the command-line parameter is a file.
 * If so, the function splits it and returns the vector with the data.
 * @param argc number of parameters
 * @param argv the parameters
 * @return the data vector
 */
vector<string> Lexer::lexer(int argc, char **argv) {
    if (argc >= 1){
        string string = argv[1];
        return fromTxtToData(string);
    }
    perror("File not inserted");

    return vector<string>();
}

/**
 * The function reads lines from the file. Each line is split by variables, operators, commands, etc.
 * Finally, it returns a vector so that each cell has an operator, command, or expression.
 * @param fileName the file to read from
 * @return the splited data
 */
vector<string> Lexer::fromTxtToData(string fileName) {
    ifstream inputFile;
    inputFile.open(fileName);
    if (!inputFile.is_open()){
        throw "error opening file";
    }
    vector<string> data;
    string token;
    for(string line; getline(inputFile, line);){
        for (unsigned int j =0; j<line.length(); j++){
            char cur= line[j];
            // if the cur is not a letter or a number so we want to put the token in the vector
            //and initialize the token
            if ((token.length()!=0) && (!isdigit(cur) &&
                                        !((cur >='A'&& cur <= 'Z')|| (cur >= 'a' && cur <= 'z') || cur == '.'))){
                data.push_back(token);
                token="";
            }

            //if saw operators
            if((cur == PLUS)|| (cur ==MINUS)|| (cur ==DIV)||(cur== MULT)) {
                string temp;
                temp += cur;
                data.push_back(temp);
                //if we sew something before =
            } else if ((cur== NOT)||(cur==GREATER)||(cur==LESS)||(cur==EQUAL)){
                if (line[j+1]== EQUAL){
                    string str;
                    str += cur;
                    str += line[j+1];
                    data.push_back(str);
                    j++;
                    //if only =
                } else {
                    string temp;
                    temp += cur;
                    data.push_back(temp);
                }
                // if we saw '(' read until his ')'.
            } else if (cur == OP_BRACKET){
                int counter = 1;
                string str;
                str += line[j];
                j++;
                while (counter != 0 && (j < line.length())){
                    if(line[j]!= SPACE){
                        str += line[j];
                    }
                    if (line[j] == OP_BRACKET){
                        counter++;
                    } else if (line[j] == CL_BRACKET){
                        counter--;
                    }
                    j++;
                }
                j-- ;
                if(counter != 0){
                    throw "syntax error";
                }
                data.push_back(str);
                //if we read from the first " to his closer and push the strings between into the vector
            } else if (cur == GERESH){
                int counter = 1;
                string str;
                str+=cur;
                j++;
                while (counter != 0 && j < line.length()){
                    str+=line[j];
                    if (line[j] == GERESH && line[j-1] != B_SLASH){
                        counter-- ;
                    }
                    j++;

                }
                j-- ;
                if (counter != 0){
                    throw "syntax error";
                }
                data.push_back(str);
                //if we saw '}' or '{' or ',' push into the vector
            } else if ((cur== F_CL_BRACKET)||(cur == F_OP_BRACKET)||cur==COMMA){
                string temp;
                temp += cur;
                data.push_back(temp);
            } else if ((cur== TAB)||(cur==SPACE)){
                continue;
            } else {
                token+= cur;
            }
        }
        if (token.length() != 0){
            data.push_back(token);
            token = "";
        }

    }
    inputFile.close();
    return arithmeticProcess(data);
}

/**
 * The function accepts a vector and connects into one cell each mathematical expression.
 * @param tempData Vector in which expressions are separated into different cells.
 * @return the new vector
 */
vector<string> Lexer::arithmeticProcess(vector<string> tempData) {
    vector<string> data;
    bool flag = false;
    // Move through the cells in the vector
    for( unsigned int i =0; i < tempData.size(); i++) {

        // check if the current cell contains IP, command or comparison operator
        if (isIp(tempData[i]) || isCommand(tempData[i]) || isCmpOperator(tempData[i]) || tempData[i] == ",") {
            flag = false;
            if (tempData[i] == ","){
                continue;
            }
            data.push_back(tempData[i]);
            continue;
        }
        // if the call contains an operator
        if (isOperator(tempData[i])) {
            string exp;
            while (isOperator(tempData[i])) {
                if (flag) {
                    flag = false;
                    exp += data.back();
                    data.pop_back();
                }
                exp += tempData[i];
                exp += tempData[i + 1];
                if (isOperator(tempData[i + 1])) {
                    exp += tempData[i + 2];
                    i += 3;
                } else {
                    i += 2;
                }
            }
            data.push_back(exp);
            --i;
        } else {
            flag = true;
            data.push_back(tempData[i]);
        }
    }
    return data;
}

/**
 * The function returns true if the received string is a command and otherwise returns false.
 * @param str the string
 * @return true or false
 */
bool Lexer::isCommand(string str) {
    return (str == CONNECT || str == PRINT || str ==ASSIGNMENT || str == BIND || str== OPEN_DATA_SERVER ||
            str == SLEEP || str == ENTERC || str == VAR || str == WHILE || str == IF);
}

/**
 * The function returns true if the received string is a IP address and otherwise returns false.
 * @param str the string
 * @return true or false
 */
bool Lexer::isIp(string str) {
    int pointCounter = 0;
    for(unsigned int i = 0; i < str.length(); i++){
        if (isdigit(str[i]) || str[i] == '.') {
            if (str[i] == '.'){
                pointCounter ++;
            }
        } else {
            return false;
        }
    }

    return pointCounter == 3;
}

/**
 * The function returns true if the received string is a comparison operator, one from: < > = >= <= !=
 * otherwise false.
 * @param str the operator
 * @return true or false
 */
bool Lexer::isCmpOperator(string str) {
    return (str[0] == LESS || str[0] == GREATER || str == EQUAL_E || str == LESS_E || str == GREATER_E || str == NOT_E);
}

/**
 * The function returns true if the received string is a arithmetic operator, one from: + - * /
 * otherwise false.
 * @param str  the operator
 * @return true or false
 */
bool Lexer::isOperator(string str) {
    return (str[0] == PLUS || str[0] == MINUS || str[0] == MULT || str[0] == DIV);

}