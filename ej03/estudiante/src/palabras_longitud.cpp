/**
 * @file palabras_longitud.cpp
 * @brief Prueba el funcionamiento del TDA Dictionary
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */
#include "dictionary.h"
#include <fstream>

int main(int argc, char* argv[]){

    Dictionary aux;
    ifstream fentrada;
    fentrada.open(argv[1]);

    if(!fentrada.is_open()){
        cout << "Error al abrir el fichero" << argv[1] << endl;
        cerr << "Error en open()" << endl;
        return -1;
    }

    string str1;
    while(fentrada){
        fentrada >> str1;
        aux.insert(str1);
    }

    fentrada.close();

    vector<string> v(aux.wordsOfLength(atoi(argv[2])));
    vector<string>::iterator it;

    cout << "Palabras de longitud " << atoi(argv[2]) << endl;
    for(it = v.begin(); it != v.end(); ++it)
        cout << (*it) << endl;

    return 0;
}