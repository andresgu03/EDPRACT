/**
 * @file letters_bag.h
 * @brief Archivo de especificación del TDA LettersBag
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */
#ifndef P04_JUEGO_LETRAS_LETTERS_BAG_H
#define P04_JUEGO_LETRAS_LETTERS_BAG_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include "bag.h"
#include "letters_set.h"

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag {
    /**
    @page page_repLettersBag Representación del TDA LettersBag

    @section sec_LettersBag LettersBag

    El **TDA LettersBag** se corresponde con un Bag de caracteres. Estos caracteres se identifican como letras.
    Su principal utilidad reside en permitir interpretar el contenido de un LettersSet, para luego poder extraer letras de forma aleatoria.

  **/
private:
    Bag <char> letters;

public:

    /**
     * @brief Constructor por defecto.
     */
    LettersBag() = default;

    /**
     * @brief Constructor dado un LettersSet.
     * Dado un LettersSet como argumento, este constructor debe rellenar la LettersBag con las letras que contiene el
       LettersSet, introduciendo cada letra el número de veces indicado por el campo LetterInfo::repetitions. Un ejemplo
       de ejecución en el que se utilice este constructor es el siguiente:
     * @code{.cpp}
     ifstream archivo_letras("letras.txt");

     LettersSet conjunto_letras;
     archivo_letras >> conjunto_letras;

     LettersBag bolsa_letras(conjunto_letras);
     * @endcode
     * @param letterSet TDA LettersSet a parsear
     */
    LettersBag(const LettersSet & letterSet);

    /**
     * @brief Introduce una letra en la bolsa.
     * @param I letra a añadir a la LettersBag
     */
    inline void insertLetter(const char & I) {this->letters.add(I);};

    /**
     * @brief Extrae una letra aleatoria de la bolsa, eliminándola del conjunto.
     * @return char representando la letra extraída
     */
    inline char extractLetter() {return this->letters.get();};

    /**
     * @brief Extrae un conjunto de letras de la bolsa, eliminándolas del conjunto.
     * @param num Número de letras a extraer
     * @return Lista con las letras extraídas aleatoriamente
     */
    std::vector<char> extractLetters(int num);

    /**
     * @brief Vacía la LettersBag, eliminando todo su contenido.
     */
    inline void clear() {this->letters.clear();};

    /**
     * @brief Tamaño de la bolsa.
     * @return int con el tamaño de la bolsa
     */
    inline unsigned int size() const {return this->letters.size();};

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param other objeto de tipo LettersBag del que se va a realizar la copia.
     * @return Referencia a this, de esta forma el operador puede ser encadenado
     */
    LettersBag& operator=(const LettersBag & other);

};

#endif //P04_JUEGO_LETRAS_LETTERS_BAG_H
