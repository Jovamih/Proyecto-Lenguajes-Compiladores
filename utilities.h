#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>
#include<map>
#include<ctype.h>

using namespace std;

map<string,string> readTableOfSysmbols(string path){
    ifstream file(path);
    string line;
    map<string,string> tabla; //usamos un diccionario
    //file.open(path);
    if(file.is_open()){
       while(getline(file,line)){
           if(!line.empty()){
               string tipo=line.substr(0,line.find(":"));
               string valor=line.substr(line.find(":")+1,-1);
            tabla[tipo]=valor;
           }
       }
    }else{
        cout<<"No se encuentra el archivo de la tabla de simbolos";
    }
   // tabla.
    return tabla;
}


struct Token{
    string type="";
    string value="";
};

class Tokenizer{
    private:
        int currentIndex=0;
        string possibleTokens="";
    public:
        Tokenizer(string);
        bool hasNextToken();
        Token nextToken();
};
Tokenizer:: Tokenizer(string token){
    possibleTokens=token;
   // cout<<token<<endl;
}
Token Tokenizer:: nextToken(){
    Token token;
    do{
    char character=possibleTokens[currentIndex];
    if(isalpha(character)){
        while(isalpha(character) || isdigit(character) ){
            token.value+=character;
            currentIndex++;
            character=possibleTokens[currentIndex];
        }
        token.type="ID";
    }else if(isdigit(character)){
        while(isdigit(character)){
            token.value+=character;
            currentIndex++;
            character=possibleTokens[currentIndex];
        }
        token.type="NUM";
    }else if(string("{},;!%&/()=?*+-|").find(character)!=-1){
         
         currentIndex++;
         char nextChar=possibleTokens[currentIndex];
         if(character=='/'&&nextChar=='/'){
           currentIndex=possibleTokens.length();
           break;
         } 
         else{
             token.value+=character;
         if((character=='+'&&(nextChar=='+' || nextChar=='=')) ||
           (character=='-' &&(nextChar=='-' || nextChar=='=')) ||
           (character=='='&&nextChar=='=') ||
           (character=='*'&&(nextChar=='*' || nextChar=='=')) ||
           (character=='/'&&nextChar=='=') ){
            
            token.value+=nextChar;
            currentIndex++;
            
        }
        token.type="OP";
        }
        //si existe commentario lo esquivamos hasta el final de la linea   
    }else{
        //si no es un caracter reconocido, pues eguimos avanzando
        //puede ser: '', ' ',^
        currentIndex++;
    }
    }while(token.type.empty());
    return token;
} 
bool Tokenizer:: hasNextToken(){
    if(possibleTokens.length()>currentIndex) return true;
    else return false;
    //return currentIndex<0
}
