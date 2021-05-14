/**
 * * Assignment-3 of Compiler Design
 * * @written by Shubham Kumar, Rajarshi Roychoudhary, Arka Maji, Susanka Mazumdar
 * * All Tokens Functions header file
*/


#include<bits/stdc++.h>
using namespace std;
#define ERROR "ERROR"


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
