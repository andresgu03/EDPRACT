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
    ifstream entrada;
    entrada.open(argv[1]);

    if(!entrada.is_open()){
        cout << "Error al abrir el fichero" << argv[1] << endl;
        cerr << "Error en open()" << endl;
        return -1;
    }

    string cad;
    while(entrada){
        entrada >> cad;
        aux.insert(cad);
    }

    entrada.close();

    vector<string> v(aux.wordsOfLength(atoi(argv[2])));
    vector<string>::iterator it;

    cout << "Palabras de longitud " << atoi(argv[2]) << endl;
    for(it = v.begin(); it != v.end(); ++it)
        cout << (*it) << endl;

    return 0;
}