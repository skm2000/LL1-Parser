#include"Token.h"

class SymbolTable{
    public:
        unordered_map<string,vector<Token>>string_tokens;
        fstream  symtabfile;
        fstream tokenfile;
        
        SymbolTable(){            
        }

        void insertInFile(Token t){
        }
        
        SymbolTable(string symbol_table_file = "symbol_tab_file.txt", string token_file = "token_file.txt"){ 
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
        }

        bool insert_token(Token * t){
            if(string_tokens.find(t->token) == string_tokens.end()){
                vector<Token> newVec;
                newVec.push_back(*t);
                string_tokens.insert({t->token,newVec});
                return false;
            }
            else{
                string_tokens[t->token].push_back(*t);
                return true;
            }
        }

        void displatSym(){
            for(auto x : string_tokens){
                for(auto y : x.second){
                    y.displayToken();
                }
            }
        }

};





















