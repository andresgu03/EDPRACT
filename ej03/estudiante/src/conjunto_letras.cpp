
/**
 * @file conjunto_letras.cpp
 * @brief Prueba el funcionamiento del TDA LettersSet
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */

#include "letters_set.h"
#include <fstream>

int main(int argc, char* argv[]){

    LettersSet letras;
    ifstream fentrada;
    fentrada.open(argv[1]);

    if(!fentrada.is_open()){
        cout << "Error al abrir el fichero" << argv[1] << endl;
        cerr << "Error en open()" << endl;
        return -1;
    }
    fentrada >> letras;
    fentrada.close();

    int score = letras.getScore(argv[2]);

    cout << score << endl;
    return 0;
}