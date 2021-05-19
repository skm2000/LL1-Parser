/**
 * * Assignment-3 of Compiler Design
 * * @written by Shubham Kumar, Rajarshi Roychoudhary, Arka Maji, Susanka Mazumdar
 * * Token header file
*/


#include "SymbolTable.h"
#include "AllTokensFunctions.h"
#define ERROR "ERROR"


SymbolTable * symtab;
SymbolTable * errortab;
bool is_being_declared = false;

/**
 * ? insertInTable() function
 * * takes the current string, row no, col no and scope as the parameters,
 * * determineToken checks whether the string is a valid one or not,
 * * insert_token inserts into symbol table file and token file accordingly(whichever needed where),
 * * if token_id is char | string then is_being_declared = true, 
 * * if token_id is "ERROR" or if it not inserted into symboltable ,
 * * then insert into error table and exit program;
*/

void insertInTable(string s,int row,int column,int scope){
    string token_id = determineToken(s);
    Token * t;
    t = new Token(s,token_id,row,column,scope,is_being_declared); 
    if(token_id==ERROR){
        errortab->insert_token(t);
        cout<<"Invalid token "<<s<<endl;
        errortab->closeFile();
        exit(1);
    }
    if(!symtab->insert_token(t)){
        errortab->insert_token(t);
        cout<<"Error inserting in symbol table token "<<s<<endl;
        errortab->closeFile();
        exit(1);
    }
    else{
        if(token_id=="id" && is_being_declared){
            is_being_declared=false;
        }
    }
    if(token_id =="char" || token_id=="string"){
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

        /**
         * ? lastCharPending = l;
         * * if current character is <, >, +, -,
         * * then l is true and lastchr = current character, check for the lastchr,
         * * if lastchr is < | > check for current ch, if ch is = then combine and call insertInTable function,
         * * if lastchr is + | - check for current ch, if ch is + | - then combine and call insertInTable function,
         * * and after inserting in table, l = false;
        */

        if(lastCharPending){
            if(lastchr == '<' || lastchr == '>'){
                if(ch=='='){
                    s+=lastchr;
                    s+=ch;
                    insertInTable(s,row,column,scope);
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
            else{
                if(lastchr == '+' && ch == '+'){
                    s+=lastchr;
                    s+=ch;
                    insertInTable(s,row,column,scope);
                    s="";
                    lastCharPending = false;
                    continue;     
                }
                else if(lastchr == '-' && ch == '-'){
                    s+=lastchr;
                    s+=ch;
                    insertInTable(s,row,column,scope);
                    s="";
                    lastCharPending = false;
                    continue;
                }
                else{
                    string token_new = toString(lastchr);
                    insertInTable(token_new,row,column,scope);
                    //updateSymbolTable(lastchr,determineTokenId(chr),row,column,scope);
                    s = "";
                }
            }
            lastCharPending = false;
        }

        /**
         * * If s is empty, then convert the char to string and then 
         * * call the insertInTable function,
         * * then empty the string
        */

        if(ch == ')' || ch == '(' || ch == ';' || ch == ','){
            if(s != ""){
                insertInTable(s,row,column,scope);
            }
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            s = "";
        }

        if(ch=='{'){
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            scope++;
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            s="";
        }

        if(ch=='}'){
            if(s!=""){
                insertInTable(s,row,column,scope);
            }
            scope--;
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            s="";
        }

        /**
         * ? isDelimiter() block
         * * If I find a space(+) or tab(+) and if the current string is not
         * * either of the delimiter characters then i'll
         * * call the function insertInTable() and then empty the contents 
         * * of the current string;
        */

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


        if(ch == '<' || ch == '>' || ch == '+' || ch == '-'){
            if(s != ""){
                insertInTable(s,row,column,scope);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s = "";
            lastchr = ch;
            lastCharPending = true;
        }


        if(ch == '='){
            if(s != ""){
                insertInTable(s,row,column,scope);
            }
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            string token_new = toString(ch);
            insertInTable(token_new,row,column,scope);
            //updateSymbolTable(s,determineTokenId(s),row,column,scope);
            s = "";
        }

        /**
         * ? openingsinglequote " ' "
         * * If I find a ' then set openingsinglequote as true,
         * * then read the characher present(since there can be only one letter),
         * * after reading if i find a ' then insert into table else ERROR generated.
        */

        if(ch == '\''){
            if(opensinglequote){
                s += '\'';
                insertInTable(s,row,column,scope);
                s = "";     
                opensinglequote = false;
            }
            else{
                opensinglequote = true;
                s += '\'';
            }
        }

        /**
         * ? openingdoublequote ' " '
         * * If I find a " then set openingdoublequote as true,
         * * then read the characher present(since there can be stream of chars),
         * * after reading if i find a "" then insert into table else ERROR generated.
        */

        if(ch == '\"'){
            if(opendoublequote){
                s += '\"';
                insertInTable(s,row,column,scope);
                s = "";     
                opendoublequote = false;
            }
            else{
                opendoublequote = true;
                s += '\"';
            }
        }

        // * If numeric or alphabet concatenate each characters
        if(isNum(ch) || isAlpha(ch)){
            s += ch;
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
    generateTokens("../../Input/test.c");   
    return 0;
}

