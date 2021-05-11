#include<bits/stdc++.h>
using namespace std;

class Token{
    public:
        string token;
        string token_id;
        int row;
        int column;
        int scope;

        Token(string token, string token_id,int row, int column,int scope){
            this->token = token;
            this->token_id = token_id;
            this->row = row;
            this->column = column;
            this->scope = scope;
        }

        string getToken(){
            return this->token;
        }

        string getTokenId(){
            return this->token_id;
        } 

        int getRow(){
            return this->row;
        }

        int getColumn(){
            return this->column;
        }
        int getScope(){
            return this->scope;
        } 

        void displayToken(){
            cout<<this->token<<"\t\t"<<this->token_id<<"\t\t"<<this->row<<"\t\t"<<this->column<<"\t\t"<<this->scope<<endl;
        }
};

