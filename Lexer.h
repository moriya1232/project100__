

#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;
/*
 * this class represent a lexer that get a line and split her into
 * a vector of strings,by the rules.
 * what separates phrases can be any "white space"
 */
class Lexer {

private:
    bool isCommand(string str);
    bool isIp(string str);
    bool isCmpOperator(string str);
    bool isOperator(string str);
    vector<string> fromTxtToData (string fileName);
    vector<string> arithmeticProcess(vector<string> data);
public:
    vector<string> lexer(int argc ,char* argv[]);
    Lexer();



};


#endif //LEXER_H