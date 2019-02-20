#include "Lexer.h"
#include "Parser.h"
#include "SymbolTableManager.h"
#include <vector>


int main(int argc, char **argv) {

    //create empty symbolTableManager
    SymbolTableManager stm;
    //read the file
    Lexer lexer;
    vector<string> vec = lexer.lexer(argc, argv);
    //parser
    Parser parser(vec,&stm);
    parser.parser();
    stm.closeSockets();

    return 0;
}