#include "dictionary.h"

int Dictionary::getOccurrences(const char c) {
    int occurrences = 0 ;
    set<string>::iterator it_st ;
    for (it_st = words.begin() ; it_st != words.end() ; ++it_st ){
        for ( int i = 0 ; i < (*it_st).length() ; i++){
            if((*it_st).at(i) == tolower(c))
                occurrences++ ;
        }
    }
    return (occurrences) ;
}

int Dictionary::getTotalLetters() {
    int total_letters = 0 ;
    set<string>::iterator it_st ;
    for (it_st = words.begin(); it_st != words.end(); ++it_st ){
        total_letters += (*it_st).length() ;
    }
    return (total_letters) ;
}

vector<string> Dictionary::wordsOfLength(int length) {
    vector<string> words_valid ;
    set<string>::iterator it_st ;
    for (it_st = words.begin(); it_st != words.end(); ++it_st ){
        if( (*it_st).length() == length){
            words_valid.insert(words_valid.end(),*it_st) ;
        }
    }
    return (words_valid) ;
}

ostream & operator <<(ostream & os, const Dictionary & dic){

    os << "Palabra";

    set<string>::const_iterator it_st;

    for(it_st = dic.words.begin(); it_st != dic.words.end(); ++it_st) {
        os << *it_st << "\n";
    }

    return os;
}

istream & operator >>(istream & is, Dictionary & dic){

    string str;
    getline(is,str);
    string palabra ;


    while(is){
        is >> palabra ;
        dic.insert(palabra);
    }

    return is;
}