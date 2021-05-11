#include"Token.h"

class SymbolTable{
    public:
        map<string,vector<Token>>string_tokens;
        fstream  symtabfile;
        fstream tokenfile;

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
            symtabfile << "============================SYMBOL TABLE==========================\n";
            symtabfile <<"\n-------------------------------------------------------------------------\n";
            symtabfile << "|TOKEN\t\t" << "TOKEN_ID\t\t" << "ROW\t\t" <<"COLUMN\t\t" << "SCOPE|\n";
            symtabfile <<"\n-------------------------------------------------------------------------\n";
            // symtabfile >> "Token" >>"\t\t" >> "Token_ID" >>"\t\t"
        }

        bool insert_token(Token * t){
            if(t->token_id=="eof"){
                tokenfile << t->token_id <<endl;
                symtabfile.close();
                tokenfile.close();
                this->displaySym();
            }
            else{
                tokenfile << t->token_id<<" ";
                symtabfile << "|" << t->token << "\t\t" << t->token_id << "\t\t" << t->row << "\t\t" << t->column << "\t\t" << t->scope << "\n";
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

        void displaySym(){
            for(auto x : string_tokens){
                for(auto y : x.second){
                    y.displayToken();
                }
            }
        }

};






















