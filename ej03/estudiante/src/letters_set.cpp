#include "letters_set.h"

int LettersSet::getScore( string word) {
    int score = 0 ;
    for (int i = 0 ; i < word.length() ; i++){
        score += letters.find((toupper(word.at(i))))->second.score ;
    }
    return (score) ;
}

LettersSet & LettersSet::operator= (const LettersSet & cl ){
    if(&cl != this)
        letters = cl.letters;

    return *this;
}

LetterInfo & LettersSet::operator[] (const char & val){
    return letters[val];
}

ostream & operator <<(ostream & os, const LettersSet & cl){

    os << "Letra " << "Cantidad " << "Puntos";

    map<char,LetterInfo>::const_iterator it_st;

    for(it_st = cl.letters.begin(); it_st != cl.letters.end(); ++it_st) {
        os << it_st->first << "\t" << it_st->second.repetitions  << "\t" << it_st->second.score;
        os << "\n";
    }

    return os;
}

istream & operator >>(istream & is, LettersSet & cl){

    string str;
    getline(is,str);
    LetterInfo aux;
    char letter;

    while(is){
        is >> letter;
        is >> aux.repetitions;
        is >> aux.score;
        pair<char,LetterInfo> pareja(letter,aux);
        cl.insert(pareja);
    }

    return is;
}