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

    /**
     * @brief TDA iterator de la clase Dictionary
     *
     *
     * Permite recorrer una instancia de la clase Dictionary permitiendo modificaciones, por lo que solo
     * se puede usar con contenedores no constantes.
    */
    class iterator{
    private:
        set<string>::iterator it;

    public:

        /**
         * @brief Constructor sin parámetros. Crea un iterador nulo
         */
        iterator(){}

        /**
         * @brief Constructor de copia
         * @param otro iterador de un conjunto de strings que se desea copiar
         */
        iterator(const set<string>::iterator& otro):it(otro){}

        /**
         * @brief Constructor de copia
         * @param otro iterador que se desea copiar
         */
        iterator(const iterator& otro):it(otro.it){}
        /**
         * @brief Destructor
         */
        ~iterator(){}

        /**
         * @brief Operador de asignación
         * @param otro iterador de un conjunto de strings que se desea copiar
         * @return puntero al iterador llamante
         */
        iterator& operator=(const set<string>::iterator& otro){it=otro;return *this;}
        /**
         * @brief Operador de asignación
         * @param otro iterador que se desea copiar
         * @return puntero al iterador llamante
         */
        iterator& operator=(const iterator& otro){it=otro.it;return *this;}
        /**
         * @brief Operador * (obtiene el objeto al que apunta el iterador).
         * @pre El iterador llamante es distinto de end()
         * @return String del diccionario al que apunta el iterador.
         */
        string operator*()const{return *it;}
        /**
         * @brief Operador ++(elemento).
         * @pre El iterador llamante es distinto de end()
         * @return puntero al iterador llamante
         * @post El iterador apunta una posición más a la derecha
         */
        iterator& operator++(){++it;return *this;}
        /**
         * @brief Operador --(elemento).
         * @pre El iterador llamante es distinto de begin().
         * @return puntero al iterador llamante
         * @post El iterador apunta una posición más a la izquierda
         */
        iterator& operator--(){--it;return *this;}
        /**
         * @brief Operador (elemento)++.
         * @pre El iterador llamante es distinto de end()
         * @return puntero al iterador llamante.
         * @post El iterador apunta una posición más a la derecha
         */
        iterator& operator++(int){it++;return *this;}
        /**
          * @brief Operador (elemento)--.
          * @pre El iterador llamante es distinto de begin().
          * @return puntero al iterador llamante
          * @post El iterador apunta una posición más a la izquierda
          */
        iterator& operator--(int){it--;return *this;}
        /**
         * @brief Operador de desigualdad
         * @param otro iterador con el que se va a comparar el iterador llamante
         * @return "false" si apuntan a la misma posición y "true" si no.
         */
        bool operator!=(const iterator& otro){return it != otro.it;}
        /**
         * @brief Operador de igualdad
         * @param otro iterador con el que se va a comparar el iterador llamante
         * @return "true" si apuntan a la misma posición y "false" si no.
         */
        bool operator==(const iterator& otro){return it == otro.it;}
    };

    /**
     * @brief Devuelve un iterador que apunta al comienzo del diccionario
     * @return iterador apuntando al principio del conjunto de palabras
     */
    iterator begin(){iterator i = words.begin();return i;}

    /**
     * @brief Devuelve un iterador que apunta al final del diccionario (posición después de la última)
     * @return iterador apuntando al final del conjunto de palabras
     */
    iterator end(){iterator i = words.end();return i;}

    /**
     * @brief TDA const_iterator de la clase Dictionary, señala a los elementos contenidos en él.
     *
     *
     * Permite recorrer una instancia de la clase Dictionary pero no modificarla, por lo que se puede usar tanto con objetos
     * Dictionary constantes y no constantes.
     */
    class const_iterator{
    private:
        set<string>::const_iterator it;

    public:

        /**
         * @brief Constructor sin parámetros
         */
        const_iterator(){}
        /**
         * @brief Constructor de copia
         * @param otro iterador constante de un conjunto de strings que se desea copiar
         */
        const_iterator(const set<string>::const_iterator& otro):it(otro){}
        /**
         * @brief Constructor de copia
         * @param otro iterador constante que se desea copiar
         */
        const_iterator(const const_iterator& otro):it(otro.it){}
        /**
         * @brief Destructor
         */
        ~const_iterator(){}
        /**
         * @brief Operador de asignación
         * @param otro iterador constante de un conjunto de strings que se desea copiar
         * @return puntero al iterador llamante
         */
        const_iterator& operator=(const set<string>::const_iterator& otro){it=otro;return *this;}
        /**
         * @brief Operador de asignación
         * @param otro iterador constante que se desea copiar
         * @return puntero al iterador llamante
         */
        const_iterator& operator=(const const_iterator& otro){it=otro.it;return *this;}
        /**
         * @brief Operador * (obtiene el objeto al que apunta el iterador).
         * @pre El iterador llamante es distinto de end()
         * @return String del diccionario al que apunta el iterador.
         */
        const string operator*()const{return *it;}
        /**
         * @brief Operador ++(elemento).
         * @pre El iterador llamante es distinto de end()
         * @return puntero al iterador llamante
         * @post El iterador apunta una posición más a la derecha
         */
        const_iterator& operator++(){++it;return *this;}
        /**
         * @brief Operador --(elemento).
         * @pre El iterador llamante es distinto de begin().
         * @return puntero al iterador llamante
         * @post El iterador apunta una posición más a la izquierda
         */
        const_iterator& operator--(){--it;return *this;}
        /**
         * @brief Operador (elemento)++.
         * @pre El iterador llamante es distinto de end()
         * @return puntero al iterador llamante.
         * @post El iterador apunta una posición más a la derecha
         */
        const_iterator& operator++(int){it++;return *this;}
        /**
          * @brief Operador (elemento)--.
          * @pre El iterador llamante es distinto de begin().
          * @return puntero al iterador llamante
          * @post El iterador apunta una posición más a la izquierda
          */
        const_iterator& operator--(int){it--;return *this;}
        /**
        * @brief Operador de desigualdad
        * @param otro iterador constante con el que se va a comparar el iterador llamante
        * @return "false" si apuntan a la misma posición y "true" si no.
        */
        bool operator!=(const const_iterator& otro){return it != otro.it;}
        /**
         * @brief Operador de igualdad
         * @param otro iterador constante con el que se va a comparar el iterador llamante
         * @return "true" si apuntan a la misma posición y "false" si no.
         */
        bool operator==(const const_iterator& otro){return it == otro.it;}
    };

    /**
     * @brief Devuelve un iterador constante que apunta al comienzo del diccionario
     * @return iterador constante apuntando al principio del conjunto de palabras
     */
    const_iterator begin() const{const_iterator i = words.begin();return i;}

    /**
     * @brief Devuelve un iterador constante que apunta al final del diccionario (posición después de la última)
     * @return iterador constante apuntando al final del conjunto de palabras
     */
    const_iterator end() const{const_iterator i = words.end();return i;}
};
#endif
