#!/bin/bash

cd Output
rm -r *.csv
cd ..
cd Lexer/include
g++ Token.h
g++ AllTokensFunctions.h
g++ SymbolTable.h
g++ Lexer.cpp
./a.out INPUTFILENAME
cd ../../
javac ParserDriver.java
java ParserDriver tokens.tok mygrammar3.g output.csv -v