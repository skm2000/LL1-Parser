#!/bin/bash

cd Output
cd ..
cd Lexer/include
g++ Lexer.cpp
./a.out INPUTFILENAME
cd ../../
javac ParserDriver.java
java ParserDriver tokens.tok mygrammar3.g output.csv -v