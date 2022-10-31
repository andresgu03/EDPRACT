#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include <map>
#include <string>

using namespace std;

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

struct LetterInfo{
    int repetitions ;
    int score ;
};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */

class LettersSet{
    /**
    @page page_repMaxStack Representación de MaxStack

    @section sec_Max_Stack MaxStack

    El **TDA MaxStack** se corresponde con una pila de _elements_ donde se almacenan valores siguiendo la jerarquía **LIFO** (_Last In first Out_) donde los elementos se almacenan de manera que sólo pueden insertarse y accedera a ellos por el _tope_ de la pila. El último elemento en añadirse será el primero al que se acceda por el tope de la pila, mientras que los primeros insertados irán quedando siguiendo dicha jerarquía en el _fondo_ de la pila. Al momento de acceder a un valor se indicará también el valor máximo de la pila en ese momento.

  **/
private:
    map <char, LetterInfo> letters;
public:
    /**
      * @brief Constructor por defecto.
      * Crea un LettersSet vacío.
      */
    inline LettersSet(){};

    /**
      * @brief Constructor de copia.
      * @param other LettersSet a copiar.
      */
    inline LettersSet(const LettersSet & other){
        this->letters = other.letters ;
    };

    /**
      * @brief Inserta un elemento en el LettersSet.
      * @param val Pareja de letra y Letterinfo asociada a insertar.
      * @return booleano que marca si se ha podido insertar la letra en el LettersSet. La letra sólo se inserta correctamente si no estaba aún incluida en la colección.
      */
    inline bool insert(const pair<char, LetterInfo> & val ){
        return ( (this->letters.insert(val)).second);
    };

    /**
      * @brief Elimina un carácter del LettersSet.
      * @param key Carácter a eliminar
      * @return Booleano que indica si se ha podido eliminar correctamente la letra del LettersSet
      */
    inline bool erase(const char & key){
        return ( this->letters.erase(key));
    };

    /**
      * @brief Limpia el contenido del LettersSet.
      * Elimina el contenido del LettersSet
      */
    inline void clear(){
        this->letters.clear() ;
    };

    /**
      * @brief Consulta si el LettersSet es vacío
      * @return true si el LettersSet está vacío, false en caso contrario.
      */
    inline bool empty() const{
        return ( this->letters.empty()) ;
    };

    /**
      * @brief Tamaño del LettersSet
      * @return Número de elementos en el LettersSet
      */
    inline int size() const{
        return ( this->letters.size()) ;
    } ;

    /**
      * @brief Calcula la puntuación dada una palabra.
      * @param word String con la palabra cuya puntuación queremos calcular.
      * @return Puntuación de la palabra, calculada como la suma de las puntuaciones de cada una de las letras.
      */
    int getScore( string word);

    /**
      * @brief Sobrecarga del operador de asignación.
      * @param cl LettersSet a copiar
      * @return Referencia al objeto this para poder encadenar el operador.
      */
    LettersSet & operator=(const LettersSet & cl);

    /**
      * @brief Sobrecarga del operador de consulta.
      * Permite acceder a los elementos del map que hay en nuestra clase.
      * @param val Carácter a consultar
      * @return Estructura de tipo Letterinfo con la información del carácter consultado. Número de repeticiones y puntuación.
      */
    LetterInfo & operator[]( const char & val );

};

/**
      * @brief Sobrecarga del operador de salida.
      * @param os Flujo de salida, donde escribir el LettersSet
      * @param cl LettersSet que se escribe.
      */
ostream & operator<<( ostream & os , const LettersSet & cl );

/**
      * @brief Sobrecarga del operador de entrada.
      * @param is Flujo de salida, del que leer el LettersSet.
      * @param cl LettersSet en el que se almacena la información leída.
      */
istream & operator>>( istream & is , LettersSet & cl );

#endif
