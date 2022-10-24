/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author Pablo García Bas
 * @author Andrés Gutiérrez Armenteros
 */

#include <stack>
#include <iostream>

struct element{

    int value;
    int max;

};

/**
  @brief T.D.A. MaxQueue

  Una instancia del tipo de dato abstracto MaxQueue nos permite usar colas de enteros con máximo.

  En cada elemento de la cola (miembro del struct "element"), se almacena un valor,

  así como el valor del máximo  almacenado en la cola en cada momento.

  La implementación interna hace uso de pilas.

  El TDA MaxQueue proporciona además distintas herramientas para la manipulación de dichas colas.

  Para poder usar el TDA MaxQueue se debe incluir el fichero

  \#include <maxqueue.h>

  @author Pablo García Bas
  @author Andrés Gutiérrez Armenteros

**/

class MaxQueue{

private:

    /**
      @brief Pila principal (Pila cuyos elementos son miembros del struct "element")

      los elementos de pila son miembros del struct "element" (con dos campos: value y max)

    **/
    std::stack<element> pila;

public:

    //******************
    // Métodos básicos:
    //
    // No es necesario declararlos (se llama a los metodos por defecto de la clase <stack>)
    //
    //MaxQueue(){};
    //MaxQueue(MaxQueue &other){};
    //~MaxQueue(){};
    //******************

    /**
      * @brief Añade un elemento nuevo a la cola (y actualiza el maximo).
      * @param new_value Nuevo valor (entero) a añadir.
      * @post La cola se modifica.
      */
    void push(int new_value);

    /**
      * @brief Elimina un elemento de la cola (y actualiza el maximo).
      * @post La cola se modifica.
      */
    void pop();

    //***************
    // Metodos inline
    //***************

    /**
      * @brief Accede al elemento en el frente de la cola
      * @post La cola no se modifica.
      * @return El elemento (miembro del struct element) al frente de la cola.
      */
    element front(){ return(this->pila.top()); };

    /**
      * @brief Devuelve el tamaño actual de la cola (numero de elementos).
      * @post La cola no se modifica.
      * @return El tamaño (entero).
      */
    int size(){ return(this->pila.size()); };

    /**
      * @brief Comprueba si la cola esta o no vacia.
      * @post La cola no se modifica.
      * @return true si la cola esta vacia, false en caso contrario (booleano).
      */
    bool empty(){ return(this->pila.empty()); };

};
