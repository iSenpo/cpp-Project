#include <iostream>
#include <fstream>
#include <ctime>
#include <bits/stdc++.h>
using namespace std;

bool isLetter(char l){
    if(!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))){
        return false;
    }
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