/**
 * @file bolsa_letras.cpp
 * @brief Prueba el funcionamiento del TDA LettersBag
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include "bag.h"
#include "letters_set.h"
#include "letters_bag.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2){
        cout << "Numero de argumentos incorrecto, abortando" << endl;
        cout << "Modo de empleo: ./bolsa_letras <ARCHIVO_LETRAS>" << endl;
        return -1;
    }

    else {
        // Inicializar el generador de números aleatorios
        srand(time(NULL));

        // 1) Se crea un objeto LettersSet y se rellena con la información del fichero pasado como primer argumento
        ifstream archivo_letras(argv[1]);
        LettersSet conjunto_letras;

        if(!archivo_letras.is_open()){ // Comprobación de errores al abrir el fichero de entrada
            cout << "Error abriendo el fichero" << argv[1] << endl;
            return -1;
        }

        archivo_letras >> conjunto_letras;

        // 2) Se crea un objeto LettersBag con la info del LettersSet anterior
        LettersBag bolsa_letras(conjunto_letras);

        // 3) Se extraen todas las letras del objeto LetterBag anterior y se imprimen en pantalla
        vector<char> random_letras;

        random_letras = bolsa_letras.extractLetters(bolsa_letras.size());

        for (int i = 0; i < random_letras.size(); ++i){
            cout << endl;
            cout << random_letras.at(i);
        }

        return 0;
    }
}