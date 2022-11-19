/**
 * @file bag.h
 * @brief Archivo de especificación del TDA Bag
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Noviembre 2022
 */

#ifndef __BAG_H__
#define __BAG_H__

#include <cstdlib>
#include <ctime>
#include <vector>

/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */

template <class T>
class Bag {
    /**
    @page page_repBag Representación del template Bag<T>

    @section sec_Bag Bag<T>

    El **Template Bag<T>** se corresponde con un vector de objetos del tipo T. Permite entre otras operaciones, extraer e introducir elementos de forma aleatoria.

  **/
private:
    std::vector<T> v;

public:
    /**
      * @brief Constructor por defecto.
      * Crea un objeto Bag vacío
      */
    Bag<T>() = default;

    /**
      * @brief Constructor de copia.
      * Crea una copia exacta de otro objeto de tipo Bag
      * @param other objeto de tipo Bag<T> del que se va a realizar la copia.
      */
    Bag<T>(const Bag<T>& other)
    {
        this->v(other.v);
    }

    /**
     * @brief Añade un elemento a la bolsa.
     * @param element elemento del tipo T a añadir a la bolsa
     */
    void add(const T& element)
    {
        this->v.push_back(element);
    }

    /**
     * @brief Extrae un elemento aleatorio de la bolsa.
     * Devuelve un elemento aleatorio de la bolsa y lo elimina de la misma
     * @return Elemento del tipo T extraído de la bolsa
     * @pre La bolsa no está vacía
     * @post El elemento devuelto se ha eliminado de la bolsa
     */
    T get(){
        int index = (rand() % this->size());

        T elem = this->v.at(index);
        this->v.at(index) = this->v.back();
        this->v.pop_back();

        return elem;
    }

    /**
     * @brief Elimina todos los elementos de la bolsa.
     */
    void clear(){
        this->v.clear();
    }

    /**
     * @brief Tamaño de la bolsa.
     * @return Número de elementos que hay en la bolsa
     */
    unsigned int size() const{
        return this->v.size();
    }

    /**
     * @brief Comprueba si la bolsa está vacía.
     * @return true si la bolsa está vacía, false en caso contrario
     */
    bool empty(){
        return this->v.empty();
    }

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param other Bag<T> a copiar
     * @return Referencia a this para poder encadenar el operador
     */
    const Bag<T>& operator=(const Bag<T>& other){
        this->v = other.v;
        return *this;
    }

};

#endif
