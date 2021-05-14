#include"SymbolTable.h"

struct isSpace
{
    bool operator()(unsigned c)
    {
        return (c == ' ' || c == '\n' || c == '\t');
    }
};

vector<string>untoken;
vector<string>approved_token;

void separateTokens(){
    // for(int i=0; i<untoken.size(); i++){
    //     cout<<i<<":"<<untoken[i]<<"\n";
    // }
    // for(auto x: untoken){
    //     cout << x <<" ";
    // }
    // cout<<"\n";
    for(auto x : untoken){
        string temp = x, paren, lit_paren = "";
        // cout<<temp<<" ";
        int paren_ind = -1;
        char ch;
        for(int j=0; j<temp.size(); j++){
            ch = temp[j];
            if(ch == '(' || ch == ')'){
                paren = to_string(ch);
                paren_ind = j;
                break;
            }else{
                lit_paren += ch; 
            }
        }
        if(lit_paren.size() > 0) approved_token.push_back(lit_paren);
        // if(papproved_token.push_back(paren);
        lit_paren = "";
        paren = "";
        if(paren_ind != -1){
            for(int j=paren_ind+1; j<temp.size(); j++){
                ch = temp[j];
                if(ch == '(' || ch == ')'){
                    paren = to_string(ch);
                }else{
                    lit_paren += ch;
                }
            }
        }
        approved_token.push_back(lit_paren);
        approved_token.push_back(paren);
        lit_paren = "";
        paren = "";
    }
    cout<<approved_token.size()<<"\n";
    // for(int i=0; i<approved_token.size(); i++){
    //     cout<<i<<":"<<approved_token[i]<<"\n";
    // }
}




SymbolTable * symtab;
void insertInSymbolTable(string token,string token_id,int row,int column,int scope){
    symtab->insert_token(new Token(token,token_id,row,column,scope));
}
// bool isDelimiter(char ch){



// }
void readCharByCharFile(string filename){
    char ch;
    string s, t;
    int row,column,scope;
    fstream fin(filename, ios::in);
    //  string k = "   \n\n             ";
    //  k.erase(remove_if(k.begin(), k.end(), isSpace()), k.end());
    //         cout<<k.size()<<"\n";
    
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
            s.erase(remove_if(s.begin(), s.end(), isSpace()), s.end());
            if(s.size()>0){
                string paren="", lit_paren="";
                int paren_ind = -1;
                for(int i=0; i<s.size(); i++){
                    if(s[i]=='(' || s[i]== ')' || s[i]=='{' || s[i]=='}'){
                            paren = to_string(ch);
                            paren_ind = i;
                            break;
                        }else{
                            lit_paren += ch; 
                        }
                    }
                }
            untoken.push_back(s);
            cout << s << "\n";
            s = "";
        }
    }
    if(s.size()>0) untoken.push_back(s);
    cout<<s<<"\n";
}

int main()
{
    readCharByCharFile("fil.txt");
    separateTokens();
    symtab = new SymbolTable("symtab.txt","token.txt");
}
