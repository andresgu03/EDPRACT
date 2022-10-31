#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <set>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */
class Dictionary {
    /**
    @page page_repMaxStack Representación de MaxStack

    @section sec_Max_Stack MaxStack

    El **TDA MaxStack** se corresponde con una pila de _elements_ donde se almacenan valores siguiendo la jerarquía **LIFO** (_Last In first Out_) donde los elementos se almacenan de manera que sólo pueden insertarse y accedera a ellos por el _tope_ de la pila. El último elemento en añadirse será el primero al que se acceda por el tope de la pila, mientras que los primeros insertados irán quedando siguiendo dicha jerarquía en el _fondo_ de la pila. Al momento de acceder a un valor se indicará también el valor máximo de la pila en ese momento.

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
        this->words = other.words ;
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
};
#endif
