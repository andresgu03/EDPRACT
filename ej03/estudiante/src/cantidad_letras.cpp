/**
 * @file cantidad_letras.cpp
 * @brief Prueba el funcionamiento del TDA Dictionary
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */

#include "dictionary.h"
#include "letters_set.h"
#include <fstream>

int main(int argc, char* argv[]){

    Dictionary diccionario;
    ifstream fentrada;
    fentrada.open(argv[1]);
    string str1;

    if(!fentrada.is_open()){
        cout << "Error al abrir el fichero" << argv[1] << endl;
        cerr << "Error en open()" << endl;
        return -1;
    }

    while(fentrada){
        fentrada >> str1;
        diccionario.insert(str1);
    }

    fentrada.close();

    LettersSet letras;
    ifstream fentrada2;

    fentrada2.open(argv[2]);
    fentrada2 >> letras;
    fentrada2.close();

    char letra = 'A';
    int total_letras = diccionario.getTotalLetters();

    cout << "Letra\tFAbs.\tFrel." << "\n";
    while(letra <= 'Z'){
        if(letras[letra].repetitions != 0) {
            int ocurrencias = diccionario.getOccurrences(letra);
            cout << letra << "\t" << ocurrencias << "\t" << (double)ocurrencias/total_letras << "\n";
        }
        letra++;
    }

    return 0;
}