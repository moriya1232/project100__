cmake_minimum_required(VERSION 3.13)
project(project100__)

set(CMAKE_CXX_STANDARD 11)

add_executable(project100__ main.cpp
        AssignmentCommand.cpp
        AssignmentCommand.h
        BinaryExpression.h
        BinaryExpression.cpp
        Command.h
        CommandExpression.h
        CommandExpression.cpp
        ConditionParser.cpp
        ConditionParser.h
        ConnectCommand.cpp
        ConnectCommand.h
        DataReaderServer.cpp
        DataReaderServer.h
        DefineVarCommand.cpp
        DefineVarCommand.h
        Div.cpp
        Div.h
        EnterC.cpp
        EnterC.h
        Expression.h
        IfCommand.h
        IfCommand.cpp
        Lexer.cpp
        Lexer.h
        Minus.h
        Minus.cpp
        Mul.cpp
        Mul.h
        Number.cpp
        Number.h
        OpenServerCommand.h
        OpenServerCommand.cpp
        Parser.cpp
        Parser.h
        Plus.cpp
        Plus.h
        PrintCommand.h
        PrintCommand.cpp
        ShuntingYard.cpp
        ShuntingYard.h
        SleepCommand.h
        SleepCommand.cpp
        SocketCommunication.cpp
        SocketCommunication.h
        SymbolTableManager.cpp
        SymbolTableManager.h
        TCPClient.cpp
        TCPClient.h
        TCPServer.cpp
        TCPServer.h
        WhileCommand.cpp
        WhileCommand.h)