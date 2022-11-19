#include "letters_bag.h"
#include "letters_set.h"
#include <vector>

// Constructor (Añade los caracteres de un LettersSet, tantas veces como dicte su campo "repetitions")
LettersBag::LettersBag(const LettersSet & letterSet){
    for (LettersSet::const_iterator it = letterSet.begin(); it != letterSet.end(); ++it){
        pair<char,LetterInfo> aux = *it;
        for (int i = 0; i < aux.second.repetitions; ++i)
            this->insertLetter(aux.first);
    }
}

// Extrae varias letras de forma aleatoria de la bolsa
std::vector<char> LettersBag::extractLetters(int num){
    std::vector<char> out;
    for (int i=0; i<num; ++i)
        out.push_back(extractLetter());
    return out;
}

// Operador de asignación
LettersBag& LettersBag::operator=(const LettersBag & other){
    this->letters = other.letters;
    return *this;
}