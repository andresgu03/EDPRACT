/**
 * @file partida_letras.cpp
 * @brief Programa de prueba del TDA Solver
 * @author Pablo García Bas
 * @author Andrés Gutiérrez Armenteros
 * @date Diciembre 2022
 */

#include <fstream>
#include <iostream>

#include "dictionary.h"
#include "letters_set.h"
#include "solver.h"
#include "letters_bag.h"
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 5){
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero con las letras" << endl;
        cout << "3.- Modo de juego (L=longitud, P=puntuación)" << endl;
        cout << "4.- Cantidad de letras para la partida" << endl;
        return -1;
    }

    else if((argv[3][0] != 'L') && (argv[3][0] != 'P')){
        cout << "Parametro 3 no introducido correctamente" << endl;
        cout << "Las unicas opciones validas son L y P" << endl;
        return -1;
    }

    else {
        // Inicializar el generador de números aleatorios
        srand(time(NULL));

        // 1) Cargar Diccionario
        ifstream f_diccionario(argv[1]);

        if(!f_diccionario){
            cout << "(Diccionario) No puedo abrir el fichero " << argv[1] << endl;
            return 0;
        }

        Dictionary diccionario;
        f_diccionario >> diccionario;
        f_diccionario.close();

        // 2) Cargar LettersSet
        ifstream f_letras(argv[2]);

        if(!f_letras){
            cout << "(Conjunto Letras) No puedo abrir el fichero " << argv[1] << endl;
            return 0;
        }

        LettersSet letras;
        f_letras >> letras;
        f_letras.close();

        // 3) Cargar Solver
        Solver solver(diccionario, letras);

        // 4) Cargar LettersBag
        LettersBag bolsa(letras);

        // 5) Extraer letras para la partida
        vector<char> random_letras;
        int n_letras = atoi(argv[4]);
        random_letras = bolsa.extractLetters(n_letras);

        cout << "LETRAS DISPONIBLES:" << endl;
        for(int i=0; i<random_letras.size(); i++)
            cout << (char)toupper(random_letras.at(i)) << " ";

        // 6) Buscar las soluciones e imprimir por pantalla
        pair <vector<string>,int> soluciones;
        bool jugar_por_punt = false;

        if(argv[3][0] == 'P')
            jugar_por_punt = true;

        soluciones = solver.getSolutions(random_letras, jugar_por_punt);

        cout << endl;
        cout << "SOLUCIONES:" << endl;
        for(int j=0; j<soluciones.first.size(); ++j)
            cout << soluciones.first.at(j) << " " << endl;

        cout << "PUNTUACION:" << endl;
        cout << soluciones.second << endl;
    }

    return 0;
}
