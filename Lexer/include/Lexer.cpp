#include "SymbolTable.h"
#include "AllTokensFunctions.h"
#define ERROR "ERROR"


SymbolTable * symtab;
SymbolTable * errortab;
bool is_being_declared = false;
map<int,int> scope_count_map;
string curr_dtype;
void insertInTable(string s,int row,int column,int scope){
    string token_id = determineToken(s);
    Token * t;
    //cout<<token_id<<endl;
    if((token_id!="," && token_id!="id" && token_id!="char" && token_id!="string")&& is_being_declared){
        is_being_declared=false;
    }
    //cout<<is_being_declared<<endl;
    if(is_being_declared){
        t = new Token(s,token_id,row,column,scope,scope_count_map[scope],is_being_declared,curr_dtype,scope_count_map); 
    }
    else{
        t = new Token(s,token_id,row,column,scope,scope_count_map[scope],is_being_declared,scope_count_map); 
    }
    if(token_id==ERROR){
        errortab->insert_error_token(t);
        cout<<"Invalid token "<<s<<endl;
        errortab->closeFile();

        exit(1);
    }
    if(!symtab->insert_token(t)){
        errortab->insert_error_token(t);
        cout<<"Error inserting in symbol table token "<<s<<endl;
        errortab->closeFile();
        exit(1);
    }
    // else{
    //     if(token_id=="id" && is_being_declared){
    //         is_being_declared=false;
    //     }
    // }
    if(token_id =="char" || token_id=="string"){
        curr_dtype=token_id;
        is_being_declared=true;
    }
}


void generateTokens(string filename){
    char ch;
    char lastchr;
    int row=1;
    int column=1;
    int scope=0;
    bool lastCharPending = false;
    bool opensinglequote = false;
    bool opendoublequote = false;
    string s;
    string token_id;
    Token * t;
    fstream fin(filename, fstream::in);
    while (fin >> noskipws >> ch) {
        if(lastCharPending){
        
            if(lastchr == '<' || lastchr =='>'){
                if(ch=='='){
                    s+=lastchr;
                    s+=ch;
                    insertInTable(s,row,column,scope);
                    //* cout<<s<<" ";
                    s="";
                    lastCharPending = false;
                    continue;
                }
                else{
                    //cout<<lastchr;
                    string token_new = toString(lastchr);
                    insertInTable(token_new,row,column,scope);
                    //updateSymbolTable(lastchr,determineTokenId(chr),row,column,scope);
                    s="";
                }
            }
            else{
                if(lastchr =='+' && ch=='+'){
                    s+=lastchr;
                    s+=ch;
                    insertInTable(s,row,column,scope);
                    //* cout<<s<<" ";
                    s="";
                    lastCharPending = false;
                    continue;     
                }
                else if(lastchr =='-' && ch=='-'){
                    s+=lastchr;
                    s+=ch;
                    insertInTable(s,row,column,scope);
                    //* cout<<s<<" ";
                    s="";
                    lastCharPending = false;
                    continue;
                }
                else{
                    string token_new = toString(lastchr);
                    insertInTable(token_new,row,column,scope);
                    //updateSymbolTable(lastchr,determineTokenId(chr),row,column,scope);
                    s="";
                }
            }
            lastCharPending = false;
        }
        if(ch==')' || ch=='(' || ch==';' || ch==','){
            //cout<<s<<" ";
            if(s!=""){
                //cout<<s<<endl;
                insertInTable(s,row,column,scope);
            }
            if(ch==';' && is_being_declared){
                is_being_declared=false;
            }
            //cout<<ch<<" ";
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            s="";
        }
        if(ch=='{'){
            if(scope_count_map.find(scope+1)==scope_count_map.end()){
                scope_count_map.insert({scope+1,0});
            }
            else{
                scope_count_map[scope+1]++;
            }
            //cout<<s<<" ";
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            scope++;
            //cout<<ch<<" ";
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            s="";
        }
        if(ch=='}'){
            //cout<<s<<" ";
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            scope--;
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            //cout<<ch<<" ";
            s="";
        }
        if(isDelimiter(ch)){
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s="";
        }
        if(ch=='\n'){
            column=0;
            row++;
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            s="";
        }
        if(ch=='<' || ch=='>' || ch=='+' || ch=='-'){
            //cout<<s<<" ";
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s="";
            lastchr=ch;
            lastCharPending=true;
        }
        if(ch=='='){
            //cout<<s<<" ";
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            //cout<<ch<<" ";
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s="";
        }
        if(ch=='\''){
            if(opensinglequote){
                s+='\'';
                insertInTable(s,row,column,scope);
                //cout<<s<<" ";
                s="";     
                opensinglequote = false;
            }
            else{
                opensinglequote =true;
                s+='\'';
            }
        }
        if(ch=='\"'){
            if(opendoublequote){
                s+='\"';
                insertInTable(s,row,column,scope);
                s="";     
                opendoublequote = false;
            }
            else{
                opendoublequote =true;
                s+='\"';
            }
        }
        if(isNum(ch) || isAlpha(ch)){
            s+=ch;
        }
        column++;
    }
    insertInTable("eof",row,column,scope);
    if(opensinglequote || opendoublequote || is_being_declared){
        cout<<"Error detected\n";
    }
}

int main(int argc, char** argv){
    symtab = new SymbolTable("../../Output/symboltable.csv","../../tokens.tok");
    errortab = new SymbolTable("../../Output/errortab.csv","../../error_tokens.tok");
    generateTokens("../../Input/test2.c");   
    return 0;
}

