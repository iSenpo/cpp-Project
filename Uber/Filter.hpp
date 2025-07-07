#include <iostream>
#include <fstream>
using namespace std;
bool isLetter(char l){
    if(!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))){
        return false;
    }
    return true;
}
bool isSmbl(char c){

    if(isLetter(c)){
        return true;
    }
    if('0' <= c && '9' >= c){
        return true;
    }
    if(c == '-' || c == '_'){
        return true;
    }
    return false;
}
bool isWord(string s){
    if(s.size() == 0){
        return false;
    }
    for(int i = 0; i<s.size(); i++){
        if(!isSmbl(s[i])){
            return false;
        }   
    }
    return true;
}
bool isDomain(string s){
    if(!(s.size() == 2 || s.size() == 3))
        return false;
    for(int i = 0 ; i<s.size() ; i++){
        if(!isLetter(s[i]))
            return false;
    }
   return true;
}
bool isPrefix(string s){
    if(s.size() == 0){
        return false;
    }
    int p = -1;
    string t="";
    for(int i = 0; i<s.size() ; i++){
        if(s[i] == '.'){
            if(!isWord(t)){
                return false;
            }
            t = "";
            i++;
        }
        t += s[i];
    }
    if(!isWord(t)){
        return false;
    }
    return true;
}
bool isSuffix(string s){
    if(s.size() == 0){
        return false;
    }
    int p = -1;
    for(int i = s.size()-1 ; i >= 0 ; i--){
        if(s[i] == '.'){
            p = i;
            break;
        }
    }
    if(p == -1)
        return false;
    
    string pref = "";
    for(int i = 0; i <p ; i++){
        pref += s[i];
    }
    if(!isPrefix(pref))
        return false;

    string domin = "";
    for(int i = p+1 ; i <s.size(); i++){
        domin += s[i];
    }
    if(!isDomain(domin))
        return false;

    return true;
}
bool isEmail(string s){
    int p = -1;
    for(int i = 0 ; i< s.size() ; i++){
        if(s[i] == '@'){
            p = i;
            break;
        }
    }
    if(p == -1)
        return false;
    
    string pref="";
    for(int i = 0; i<p ; i++){
        pref += s[i];
    }
    if(!isPrefix(pref))
        return false;
    
    string suff= "";
    for(int i = p+1 ; i <s.size(); i++){
        suff += s[i];
    }   
    if(!isSuffix(suff))
        return false;

    return true;
}
bool isNumber(char n){
    if(!(n >= '0' && n <= '9') ){
        return false;
    }
    return true;
}
bool isSymbol(char s){
    if(!(s == '!' || s <= '@' || s <= '#' || s <= '$' || s <= '*' || s <= '&')){
        return false;
    }
    return true;
}
bool isName(string s){
    for(int i = 0;i<s.size();i++){
        if(!isLetter(s[i])){
            return false;
        }
    }
    return true;
}
bool isUsername(string s){
    if(!isLetter(s[0])){
        return false;
    }
    for(int i=0 ; i<s.size() ; i++){
        if(!( isLetter(s[i]) || isNumber(s[i]) || s[i] == '.' )){
            return false;
        }
        if(s[i] == ' '){
            return false;
        }
    }
    return true;
}
bool isPassword(string s){
   for(int i=0 ; i<s.size() ; i++){
        if(!( isLetter(s[i]) || isNumber(s[i]) || isSymbol(s[i]) || s[i] == '.' )){
            return false;
        }
        if(s[i] == ' '){
            return false;
        }
    }
    return true; 
}
bool isPhoneNumber(string s){
    for(int i = 0 ; i< s.size() ; i++){
        if(!isNumber(s[i])){
            return false;
        }
    }
    return true;
}
bool CheckUserExist(string username,string FileName){
    fstream file(FileName,ios::in);
    if(file.is_open()){
        string user,pass;
        while( file >> user >> pass){
            if(username == user){
                file.close();
                return true;
            }
        }
        file.close();
    }else{
        cerr<<"cant open file!\n";
    }
    return false;
}
bool CheckInfo(string username,string password,string FileName){
    fstream file(FileName,ios::in);
    if(file.is_open()){
        string user,pass;
        while( file >> user >> pass){
            if(username == user && password == pass){
                file.close();
                return true;
            }
        }
        file.close();
    }else{
        cerr<<"cant open file!\n";
    }
    return false;
}
bool CheckCord(string s){
    int cama = 0;
    if(s[0] != '(' || s[s.size()-1] != ')'){
        return false;
    }
    for(int i = 0; i<s.size() ; i++){
        if(s[i] == ','){
            cama++;
        }
        if(i != 0 && i != s.size()-1){
            if(!isNumber(s[i]) && s[i] != ','){
                return false;
            }
        }
    }
    if(cama != 1){
        return false;
    }
    return true;
}