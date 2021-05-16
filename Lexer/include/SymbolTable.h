/**
 * * Assignment-3 of Compiler Design
 * * @written by Shubham Kumar, Rajarshi Roychoudhary, Arka Maji, Susanka Mazumdar
 * * Symbol Table header file
*/


#include"Token.h"

/**
 * ? SYMBOL TABLE CLASS
 * * symtabfile = a file where my symbol table is kept (.tab);
 * * tokenfile = tokens generated are kept (.tok) and this file is given as an input to the parser;
 * * map<string,vector<Token>>string_tokens = A hashmap of tokens, with key as lexeme and Tokens as a vector;
*/

class SymbolTable{

    public:

        map<string,vector<Token>>string_tokens;
        fstream  symtabfile;
        fstream tokenfile;
        
        /**
         * ? PARAMETERIZED CONSTRUCTOR SYMBOL TABLE
         * * It takes two parameters, an symbol table file name and token file name;
         * * Used to open both the files, error checks have been provided in case the file fails to open.
         * * symtabfile << : This is used to write in a file
        */

        SymbolTable(string symbol_table_file , string token_file ){ 
            symtabfile.open(symbol_table_file,ios::out);
            if(!symtabfile){
                cout<<"Error: Symbol table file"<<"\n";
                return;
            }
            tokenfile.open(token_file,ios::out);
            if(!tokenfile){
                cout<<"Error: Token table file"<<"\n";
                return;
            }
            symtabfile << "======================================SYMBOL TABLE==========================================\n";
            symtabfile << "\n--------------------------------------------------------------------------------------------\n";
            symtabfile << "|LEXEME|\t\t" << "|TOKEN|\t\t" << "|ROW|\t\t" <<"|COLUMN|\t\t" << "|SCOPE|\n";
            symtabfile << "--------------------------------------------------------------------------------------------\n";
        }

        bool insert_token(Token * t){
            if(t->token_id=="eof"){
                tokenfile << t->token_id <<endl;
                symtabfile.close();
                tokenfile.close();
                //this->displaySym();
            }
            else{
                tokenfile << t->token_id<<" ";
                symtabfile << t->token << "\t\t" << t->token_id << "\t\t" << t->row << "\t\t" << t->column << "\t\t" << t->scope << "\n";
            }
            if(string_tokens.find(t->token) == string_tokens.end()){
                vector<Token> newVec;
                newVec.push_back(*t);
                string_tokens.insert({t->token,newVec});
                // symtabfile >> t->token >> "\t\t" 
                return false;
            }
            else{
                string_tokens[t->token].push_back(*t);
                return true;
            }
        }


        /**
         * ? displaySym()
         * * Used to display the symbol table. 
        */

        void displaySym(){
            cout << "================================SYMBOL TABLE=============================\n";
            cout << "\n----------------------------------------------------------------------------\n";
            cout << "|LEXEME|\t" << "|TOKEN|\t\t     " << "  |ROW|\t" <<"     |COLUMN|\t  " << "   |SCOPE|\n";
            cout << "----------------------------------------------------------------------------\n";
            for(auto x : string_tokens){
                for(auto y : x.second){
                    y.displayToken();
                }
            }
        }

        void closeFile(){
            this->symtabfile.close();
            this->tokenfile.close();
        }

};






















