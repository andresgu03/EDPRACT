/**
 * @file dictionary.h
 * @brief Archivo de especificación del TDA Dictionary
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */
class Dictionary {
    /**
    @page page_repDictionary Representación de Dictionary

    @section sec_Dictionary Dictionary

    El **TDA Dictionary** se corresponde con un conjunto de _strings_ de manera que se trata a cada string como una palabra. Las palabras se ordenan por orden alfabético. Además, serán únicas.

  **/
private:
    set<string> words;
public:
    /**
      * @brief Constructor por defecto.
      * Crea un Dictionary vacío
      */
    inline Dictionary(){};

    /**
      * @brief Constructor de copia.
      * Crea un Dictionary con el mismo contenido que el que se pasa como argumento.
      * @param other Dictionary que se quiere copiar.
      */
    inline Dictionary( const Dictionary & other){
        set<string> aux (other.words) ;
        words = aux ;
    };

    /**
      * @brief Indica si una palara está en el diccionario o no.
      * Este método comprueba si una determinada palabra se encuentra o no en el diccionario.
      * @param palabra la palabra que se quiere buscar.
      * @return Booleano indicando si la palabra existe o no en el diccionario.
      */
    inline bool exists(const string & palabra ) const {
        return (this->words.count(palabra)) ;
    };

    /**
      * @brief Inserta una palabra en el diccionario.
      * @param val palabra a insertar en el diccionario.
      * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta con éxito si no existía previamente en el diccionario.
      */
    inline bool insert( const string & val ){
        return ((this->words.insert(val)).second );
    } ;

    /**
      * @brief Elimina una palabra del Dictionary
      * @param val palabra a borrar del diccionario
      * @return Booleano que indica si la palabra se ha borrado del diccionario.
      */
    inline bool erase ( const string & val){
        return (this->words.erase(val)) ;
    };

    /**
      * @brief Limpia el Dictionary.
      * Elimina todas las palabras contenidas en el conjunto.
      */
    inline void clear(){
        this->words.clear() ;
    };

    /**
      * @brief Comprueba si el Dictionary está vacío.
      * @return true si el diccionario está vacío, false en caso contrario.
      */
    inline bool empty() const{
        return (this->words.empty()) ;
    } ;

    /**
      * @brief Tamaño del diccionario.
      * @return Número de palabras guardadas en el diccionario.
      */
    inline unsigned int size() const{
        return (this->words.size()) ;
    } ;

    /**
      * @brief Indica el número de apariciones de una letra.
      * @param c letra a buscar
      * @return Un entero indicando el número de apariciones.
      */
    int getOccurrences(const char c) ;

    /**
      * @brief Cuenta el total de letras de un diccionario.
      * @return Entero con el total de letras.
      */
    int getTotalLetters() ;

    /**
      * @brief Devuelve las palabras en el diccionario con una longitud dada.
      * @param length Longitud de las palabras buscadas.
      * @return Vector de palabras con la longitud deseada.
      */
    vector<string> wordsOfLength ( int length) ;

    /**
      * @brief Sobrecarga del operador de salida.
      * Permite imprimir el diccionario completo a un flujo de salida.
      * @param os Flujo de salida, donde imprimir el Dictionary
      * @param dic Dictionary a imprimir.
      * @returns Flujo de salida, para poder encadenar el operador
      */
    friend ostream & operator<<(ostream & os, const Dictionary & dic);

    /**
      * @brief Sobrecarga del operador de entrada.
      * Permite leer las palabras de un fichero de texto e introducirlas en el diccionario.
      * @param is Flujo de entrada.
      * @param dic Dictionary a rellenar.
      * @returns Flujo de entrada para poder encadenar el operador
      */
    friend istream & operator>>(istream &is, Dictionary & dic);
};
#endif
