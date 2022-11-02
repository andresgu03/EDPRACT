/**
 * @file letters_set.h
 * @brief Archivo de especificación del TDA LettersSet
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */
#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include <map>
#include <string>
#include <iostream>
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

class LettersSet {
    /**
    @page page_repLettersSet Representación de LettersSet

    @section sec_LettersSet LettersSet

    El **TDA LettersSet** se corresponde con un mapa formado por _letras_ y su información correspondiente del tipo *LetterInfo*. Es decir, a cada letra le acompaña el número de veces que está repetida y la puntuación que tendrá al ser utilizada en la partida.

  **/
private:
    map<char, LetterInfo> letters;
public:
    /**
      * @brief Constructor por defecto.
      * Crea un LettersSet vacío.
      */
    inline LettersSet() {};

    /**
      * @brief Constructor de copia.
      * @param other LettersSet a copiar.
      */
    inline LettersSet(const LettersSet &other) {
        map<char, LetterInfo> aux(other.letters);
        this->letters = aux;
    };

    /**
      * @brief Inserta un elemento en el LettersSet.
      * @param val Pareja de letra y Letterinfo asociada a insertar.
      * @return booleano que marca si se ha podido insertar la letra en el LettersSet. La letra sólo se inserta correctamente si no estaba aún incluida en la colección.
      */
    inline bool insert(const pair<char, LetterInfo> &val) {
        return ((this->letters.insert(val)).second);
    };

    /**
      * @brief Elimina un carácter del LettersSet.
      * @param key Carácter a eliminar
      * @return Booleano que indica si se ha podido eliminar correctamente la letra del LettersSet
      */
    inline bool erase(const char &key) {
        return (this->letters.erase(key));
    };

    /**
      * @brief Limpia el contenido del LettersSet.
      * Elimina el contenido del LettersSet
      */
    inline void clear() {
        this->letters.clear();
    };

    /**
      * @brief Consulta si el LettersSet es vacío
      * @return true si el LettersSet está vacío, false en caso contrario.
      */
    inline bool empty() const {
        return (this->letters.empty());
    };

    /**
      * @brief Tamaño del LettersSet
      * @return Número de elementos en el LettersSet
      */
    inline int size() const {
        return (this->letters.size());
    };

    /**
      * @brief Calcula la puntuación dada una palabra.
      * @param word String con la palabra cuya puntuación queremos calcular.
      * @return Puntuación de la palabra, calculada como la suma de las puntuaciones de cada una de las letras.
      */
    int getScore(string word);

    /**
      * @brief Sobrecarga del operador de asignación.
      * @param cl LettersSet a copiar
      * @return Referencia al objeto this para poder encadenar el operador.
      */
    LettersSet &operator=(const LettersSet &cl);

    /**
      * @brief Sobrecarga del operador de consulta.
      * Permite acceder a los elementos del map que hay en nuestra clase.
      * @param val Carácter a consultar
      * @return Estructura de tipo Letterinfo con la información del carácter consultado. Número de repeticiones y puntuación.
      */
    LetterInfo &operator[](const char &val);

    /**
      * @brief Sobrecarga del operador de salida.
      * @param os Flujo de salida, donde escribir el LettersSet
      * @param cl LettersSet que se escribe.
      */
    friend ostream &operator<<(ostream &os, const LettersSet &cl);

    /**
      * @brief Sobrecarga del operador de entrada.
      * @param is Flujo de salida, del que leer el LettersSet.
      * @param cl LettersSet en el que se almacena la información leída.
      */
    friend istream &operator>>(istream &is, LettersSet &cl);

};

#endif
