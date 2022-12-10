/**
 * @file cantidad_letras.cpp
 * @brief Programa de prueba de los metodos getOccurrences y getTotalUsages del TDA Dictionary
 * @author Pablo García Bas
 * @author Andrés Gutiérrez Armenteros
 * @date Diciembre 2022
 */

#include <fstream>
#include <iostream>

#include "dictionary.h"
#include "letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 3){
      cout << "Los parametros son: " << endl;
      cout << "1.- El fichero con el diccionario" << endl;
      cout << "2.- El fichero con las letras" << endl;
      return -1;
  }

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

  // 3) Conteo de usos y ocurrencias de las letras del LettersSet en el diccionario

  char letra = 'A';

  cout << "Letra\tUsos\tOcurrencias" << "\n";

  while(letra <= 'Z'){
      if(letras[letra].repetitions != 0) {
          int ocurrencias = diccionario.getOccurrences(letra);
          int usos = diccionario.getTotalUsages(letra);

          cout << letra << "\t" << usos << "\t" << ocurrencias << "\n";
      }
      letra++;
  }

  return 0;
}