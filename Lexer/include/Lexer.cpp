#include "SymbolTable.h"
#define ERROR "ERROR"

SymbolTable * symtab;

bool isAlpha(char ch){
    return ((ch>='a' && ch<='z')||(ch>='A' && ch<='Z'));
}

bool isNum(char ch){
    return (ch>='0' && ch<='9');
}

bool isDelimiter(char ch){
    return ch==' '||ch=='\t';
}

bool isAlNum(string s){
    for(int i=0;i<s.size();i++){
        if(isAlpha(s[i] || isNum(s[i])))
        {
            return false;
        }
    }
    return true;
}

string toString(char c){
    return string(1,c);
}
//id increment decrement + - equals notequals lessthan lessthanequals greaterthan 
//greaterthanequals eof char string while charToken stringToken void , ( ) { } ; EPSILON

string determineToken(string s){
    if(s==""){
        return "";
    }
    if(s==")"){
        return ")";
    }
    if(s=="("){
        return "(";
    }
    if(s=="{")
    {
        return "{";
    }
    if(s=="}"){
        return "}";
    }
    if(s=="void"){
        return "void";
    }
    if(s=="main"){
        return "main";
    }
    if(s=="char"){
        return "char";
    }
    if(s=="string"){
        return "string";
    }
    if(s=="while"){
        return "while";
    }
    if(s==";"){
        return ";";
    }
    if(s==","){
        return ",";
    }
    if(s=="eof"){
        return "eof";
    }
    if(s=="<="){
        return "lessthanequals";
    }
    if(s == "<"){
        return "lessthan";
    }
    if(s == ">="){
        return "greaterthanequals";
    }
    if(s == ">"){
        return "greaterthan";
    }

    if(s == "="){
        return "equals";
    }
    if(s[0]=='\"')
        {
            if(s[s.size()-1]=='\"')
            {
                return "stringToken";
            }
            else{
                return ERROR;
            }
        }
    if(s[0]=='\'' && s[s.size()-1]=='\'' && s.size()==3){
        return "charToken";
    }
    if(isAlNum(s)){
        if(isNum(s[0])){
            return ERROR;
        }
        return "id";
    }
    return ERROR;
}


void generateTokens(string filename){
    char ch;
    char lastchr;
    int row=0;
    int column=0;
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
            if(ch=='='){
                s+=lastchr;
                s+=ch;
                token_id = determineToken(s);
                t = new Token(s,token_id,row,column,scope); 
                symtab->insert_token(t);
                //* cout<<s<<" ";
                s="";
                lastCharPending = false;
                continue;
            }
            else{
                //cout<<lastchr;
                string token_new = toString(lastchr);
                token_id = determineToken(token_new);
                symtab->insert_token(new Token(token_new,token_id,row,column,scope));
                //updateSymbolTable(lastchr,determineTokenId(chr),row,column,scope);
                s="";
            }
            lastCharPending = false;
        }
        if(ch==')' || ch=='(' || ch==';' || ch==','){
            //cout<<s<<" ";
            if(s!=""){
                cout<<s<<endl;
                token_id = determineToken(s);
                symtab->insert_token(new Token(s,token_id,row,column,scope));
            }
            //cout<<ch<<" ";
            string token_new = toString(ch);
            token_id = determineToken(token_new);
            symtab->insert_token(new Token(token_new,token_id,row,column,scope));
            s="";
        }
        if(ch=='{'){
            //cout<<s<<" ";
            if(s!=""){
                token_id = determineToken(s);
                t = new Token(s,token_id,row,column,scope); 
                symtab->insert_token(t);
            }
            scope++;
            //cout<<ch<<" ";
            string token_new = toString(ch);
            token_id = determineToken(token_new);
            symtab->insert_token(new Token(token_new,token_id,row,column,scope));
            s="";
        }
        if(ch=='}'){
            //cout<<s<<" ";
            if(s!=""){
                token_id = determineToken(s);
                t = new Token(s,token_id,row,column,scope); 
                symtab->insert_token(t);
            }
            scope--;
            string token_new = toString(ch);
            token_id = determineToken(token_new);
            symtab->insert_token(new Token(token_new,token_id,row,column,scope));
            //cout<<ch<<" ";
            s="";
        }
        if(isDelimiter(ch)){
            if(s!=""){
                token_id = determineToken(s);
                t = new Token(s,token_id,row,column,scope); 
                symtab->insert_token(t);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s="";
        }
        if(ch=='\n'){
            column=0;
            row++;
            if(s!=""){
                token_id = determineToken(s);
                t = new Token(s,token_id,row,column,scope); 
                symtab->insert_token(t);
            }
            s="";
        }
        if(ch=='<' || ch=='>'){
            //cout<<s<<" ";
            if(s!=""){
                token_id = determineToken(s);
                t = new Token(s,token_id,row,column,scope); 
                symtab->insert_token(t);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s="";
            lastchr=ch;
            lastCharPending=true;
        }
        if(ch=='='){
            //cout<<s<<" ";
            if(s!=""){
                token_id = determineToken(s);
                t = new Token(s,token_id,row,column,scope); 
                symtab->insert_token(t);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            //cout<<ch<<" ";
            string token_new = toString(ch);
            token_id = determineToken(token_new);
            symtab->insert_token(new Token(token_new,token_id,row,column,scope));
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s="";
        }
        if(ch=='\''){
            if(opensinglequote){
                s+='\'';
                //updateSymbolTable(s,determineTokenId(s),row,column,scope);
                if(s!=""){
                    token_id = determineToken(s);
                    t = new Token(s,token_id,row,column,scope); 
                    symtab->insert_token(t);
                }
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
                //updateSymbolTable(s,determineTokenId(s),row,column,scope);
                //cout<<s<<" ";
                if(s!=""){
                    token_id = determineToken(s);
                    t = new Token(s,token_id,row,column,scope); 
                    symtab->insert_token(t);
                }
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
    token_id = determineToken("eof");
    t = new Token(s,token_id,row,column,scope); 
    symtab->insert_token(t);
    //cout<<"eof";
    if(opensinglequote || opendoublequote){
        cout<<"Error detected\n";
    }
}

int main(){
    symtab = new SymbolTable("symboltable.tab","../tokens.tok");
    generateTokens("test.c");   
}

