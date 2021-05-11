#include"SymbolTable.h"

// void main(char c, string s)    {
//             while(c<'a'){
 //       void x ,y ,z;

//             }
// }


SymbolTable * symtab;
void insertInSymbolTable(string token,string token_id,int row,int column,int scope){
    symtab->insert_token(new Token(token,token_id,row,column,scope));
}
// bool isDelimiter(char ch){
    

// }
void readCharByCharFile(string filename){
    char ch;
    string s;
    int row,column,scope;
    fstream fin(filename, fstream::in);
    
    while (fin >> noskipws >> ch) {
        // if(ch=='\t' || ch==' ' || ch=='\n'){
        //     if(s!=""){
        //         string token_id = determineTokenId(s);
        //         insertInSymbolTable(s,token_id,row,column,scope);
        //         s="";
        //     }
        //     continue;
        // }
        if(ch != ' '){
            s += ch;
        }else{
            if(ch = ' '){
                cout << s << "\n";
                s = "";
            }
        }
        // cout<<s<<"\n";
    }
    cout<<s<<"\n";
}

int main()
{
    readCharByCharFile("fil.txt");
    symtab = new SymbolTable("symtab.txt","token.txt");
}
