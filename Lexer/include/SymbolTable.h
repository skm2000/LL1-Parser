/**
 * * Assignment-3 of Compiler Design
 * * @written by Shubham Kumar, Rajarshi Roychoudhary, Arka Maji, Susanka Mazumdar
 * * Symbol Table header file
*/


#include"Token.h"

/**
 * ? SYMBOL TABLE CLASS
 * * tabfile = a file where my symbol table is kept (.tab);
 * * tokenfile = tokens generated are kept (.tok) and this file is given as an input to the parser;
 * * map<string,vector<Token>>string_tokens = A hashmap of tokens, with key as lexeme and Tokens as a vector;
*/

class SymbolTable{

    public:

        map<string,vector<Token>>string_tokens;
        fstream tabfile;
        fstream tokenfile;
        
        /**
         * ? PARAMETERIZED CONSTRUCTOR SYMBOL TABLE
         * * It takes two parameters, an symbol table file name and token file name;
         * * Used to open both the files, error checks have been provided in case the file fails to open.
         * * tabfile << : This is used to write in a file
         * * tabfile can be symboltable file or errortablefile
         * * tokenfile can also be tokenfile or errortokenfile
        */

        SymbolTable(string symbol_table_file , string token_file ){ 
            tabfile.open(symbol_table_file,ios::out);
            if(!tabfile){
                cout<<"Error: Symbol table file"<<"\n";
                return;
            }
            tokenfile.open(token_file,ios::out);
            if(!tokenfile){
                cout<<"Error: Token table file"<<"\n";
                return;
            }
            tabfile << "|LEXEME|\t" << "|TOKEN|\t  " << "|ROW|\t  " <<"|COLUMN|\t" << "|SCOPE|\t" << "|ROW_DECLARED|\t" <<"|COLUMN_DECLARED|\t" << "|SCOPE_DECLARED|\t" <<"|IS_BEING_DECLARED|\n\n\n";
        }

        /**
         * ? INSERT TOKEN
         * * It takes a pointer to the token object;
         * * If token_id is "eof" this means that it has read the complete source file and has 
         * * generated a list of tokens, also append the "eof" in tokenfile ;
         * ? checkInsertion()
         * * checks whether the current token is liable to be inserted or not ;
         * * if the token_id is "id" then insert into the symbol table,
         * * and check whether that token corresponding to the id is resent in hashtable,
         * * if no token insert into hashtable else chain it;
        */

        bool insert_token(Token * t){
            if(t->token_id == "ERROR"){
                tabfile << "\t" << t->token << "\t\t  " << t->token_id << "\t\t" << t->row << "\t    " << t->column << "\t\t    " << t->scope <<"\t\t\t"<< t->row_declared<<"\t\t\t\t"<<t->column_declared<<"\t\t\t\t\t"<<t->scope_declared<<"\t\t\t\t"<<t->is_being_declared<<"\n";
            }
            if(t->token_id=="eof"){
                tokenfile << t->token_id <<endl;
                tabfile.close();
                tokenfile.close();
                //this->displaySym();
            }
            else{
                if(!checkInsertion(t)){
                    return false;
                }
                tokenfile << t->token_id<<" ";
                if(t->token_id=="id"){
                    tabfile << "\t" << t->token << "\t\t  " << t->token_id << "\t\t" << t->row << "\t    " << t->column << "\t\t    " << t->scope <<"\t\t\t"<< t->row_declared<<"\t\t\t\t"<<t->column_declared<<"\t\t\t\t\t"<<t->scope_declared<<"\t\t\t\t"<<t->is_being_declared<<"\n";
                }
            }
            if(t->token_id!="id"){
                return true;
            }
            if(string_tokens.find(t->token) == string_tokens.end()){
                vector<Token> newVec;
                newVec.push_back(*t);
                string_tokens.insert({t->token,newVec});
                // tabfile >> t->token >> "\t" 
            }
            else{
                string_tokens[t->token].push_back(*t);
            }
            return true;
        }

        /**
         * ? CHECK INSERTION
         * * It takes a pointer to the token object;
         * * If token_id is not "id" then it returns true,
         * * otherwise checking if the current token is in hashtable or not,
         * * and also if it has been declared or not, if declared
         * * enter into hashtable the offset of the variable where it has been declared,
         * * 
        */

        bool checkInsertion(Token * t){
            map<int,int> scope_count_map = t->scope_count_map;
            if(t->token_id!="id"){
                return true;
            }
            if(string_tokens.find(t->token)==string_tokens.end()){
                if(t->is_being_declared){
                    t->row_declared=t->row;
                    t->column_declared=t->column;
                    t->scope_declared=t->scope;
                }
                else{
                    cout<<"Not declared "<<t->token<<" "<<t->row<<" "<<t->column<<endl;
                }
                return t->is_being_declared;
            }
            if(t->is_being_declared){
                for(int i=0;i<string_tokens[t->token].size();i++){
                    if(t->scope==string_tokens[t->token][i].scope && t->scope_count==string_tokens[t->token][i].scope_count){
                        if(string_tokens[t->token][i].is_being_declared){
                            cout<<"Same token "<<t->row<<" "<<t->column<<" declared in same scope("<<string_tokens[t->token][i].row<<" "<<string_tokens[t->token][i].column<<")";
                            return false;
                        }
                    }
                }
                t->row_declared=t->row;
                t->column_declared = t->column;
                t->scope_declared = t->scope;
                return true;
            }
            else{
                t->row_declared=-1;
                t->column_declared=-1;
                t->scope_declared=-1;
                for(int i=0;i<string_tokens[t->token].size();i++){
                    if(string_tokens[t->token][i].scope>t->scope_declared 
                    && (string_tokens[t->token][i].scope<=t->scope 
                    && string_tokens[t->token][i].is_being_declared 
                    && string_tokens[t->token][i].scope_count==scope_count_map[string_tokens[t->token][i].scope]
                    )){
                        t->row_declared=string_tokens[t->token][i].row;
                        t->column_declared = string_tokens[t->token][i].column;
                        t->scope_declared = string_tokens[t->token][i].scope;
                        t->dtype = string_tokens[t->token][i].dtype;
                    }
                    
                }
                if(t->row_declared==-1){
                    cout<<"Token "<<t->token<<" "<<t->row<<" "<<t->column<<" not in the scope or redeclared"<<endl;
                }
                return t->row_declared!=-1;
            }
            return false;
        }

        /**
         * ? displaySym()
         * * Used to display the symbol table. 
        */

        void displaySym(){
            cout << "================================SYMBOL TABLE=============================\n";
            cout << "\n----------------------------------------------------------------------------\n";
            cout << "|LEXEME|\t" << "|TOKEN|\t" << "  |ROW|\t" <<"|COLUMN|\t  " << "|SCOPE|\n";
            cout << "----------------------------------------------------------------------------\n";
            for(auto x : string_tokens){
                for(auto y : x.second){
                    y.displayToken();
                }
            }
        }

        void closeFile(){
            this->tabfile.close();
            this->tokenfile.close();
        }

};






















