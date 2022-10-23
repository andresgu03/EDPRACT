/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author
 */
#include <queue>
#include <ostream>

using namespace std ;
/**
  @brief Tipo element

  Una instancia del tipo **element** contendrá un valor de tipo entero y otro entero indicando el máximo actual al acceder al elemento.

  @author Andrés Gutiérrez
  @author Pablo García
  @date Octubre 2022

**/
struct element{
    /**
     @page page_repElement Representación de Element

    @section sec_element Tipo element

    La representación del tipo **element** se basa en un struct de dos valores enteros que almacenan un valor _dato_, refiriéndose al valor del elemento y un valor _máximo_ haciendo referencia al máximo del contenedor en el momento del acceso al elemento.

    */
    int value ;
    int maximum;
    // operator << overload.
    /**
      * @brief Sobrecarga del operador << para un objeto del tipo _element_
      * @param os Flujo de salida.
      * @param element Elemento a imprimir.
      * @return Referencia al flujo de salida @os .
      */
    friend ostream & operator<<(std::ostream& os , const element obj);
};
/**
  @brief T.D.A. MaxStack

  Una instancia del tipo de dato abstracto MaxStack será una pila LIFO de elementos que serán un par de valores indicando el valor del elemento y el valor del máximo en la pila en el momento de inserción y de acceso al mismo.

  \#include <maxstack.h>

  @author Andrés Gutiérrez
  @author Pablo García
  @date Octubre 2022

**/
class MaxStack{
    /**
     @page page_repMaxStack Representación de MaxStack

     @section sec_Max_Stack MaxStack

     El **TDA MaxStack** se corresponde con una pila de _elements_ donde se almacenan valores siguiendo la jerarquía **LIFO** (_Last In first Out_) donde los elementos se almacenan de manera que sólo pueden insertarse y accedera a ellos por el _tope_ de la pila. El último elemento en añadirse será el primero al que se acceda por el tope de la pila, mientras que los primeros insertados irán quedando siguiendo dicha jerarquía en el _fondo_ de la pila. Al momento de acceder a un valor se indicará también el valor máximo de la pila en ese momento.

   **/
private :
    /**
      @brief Cola de elementos.

      q es la _cola_ ( de elements) que representará a la pila internamente. En el campo _val_ de element se almacenará el valor y en el campo _maximum_ el máximo actual.

    **/
    queue<element> q ;
public :
    /**
      * @brief Constructor por defecto .
      * @post Genera una instancia de la clase MaxStack con O elementos.
      * @return Imagen, el objeto MaxStack creado.
      */
    MaxStack() {};

    /**
      * @brief Constructor de copias.
      * @param orig Referencia a la MaxStack original que se quiere copiar.
      * @return MaxStack, el objeto MaxStack creado.
      */
    MaxStack(const MaxStack & otro) ;

    /**
      * @brief Operador de asignación .
      * @param orig Referencia a la MaxStack original que desea copiarse.
      * @return Una referencia al objeto MaxStack modificado.
      * @post Destruye cualquier información que contuviera previamente la MaxStack que llama al operador de asignación.
      */
    MaxStack & operator= ( const MaxStack & otro) ;

    /**
      * @brief Muestra el elemento del _tope_ de la pila.
      * @pre @q no vacía.
      * @return element _tope_ de la pila.
      */
    element top () ;

    /**
      * @brief Inserta un elemento a la pila.
      * @param val Valor entero que se introducirá en la pila.
      * @post El elemento será insertado junto con el máximo actual de la pila.
      */
    void push(int val);

    /**
      * @brief Elimina el elemento del _tope_ de la pila.
      * @pre @q no vacía.
      * @post La pila pasa a tener un elemento menos.
      */
    void pop () ;

    /**
      * @brief Indica si la pila está o no vacía.
      * @return valor booleano que indica _true_ si la pila está vacía o _false_ si no lo está.
      */
    bool empty(){ return (q.empty());} ;

    /**
      * @brief Indica el número de elementos que hay actualmente en la pila.
      * @return Valor entero que indica el número de elementos de la pila actualmente.
      */
    int size(){ return (q.size()) ; } ;

    /**
  * @brief Intercambia dos objetos MaxStack.
  * @param x Referencia a la MaxStack que desea intercambiarse.
  * @post El objeto actual pasa a tener los elementos de x y el objeto x pasa a tener los elementos del objeto MaxStack que llama a este método.
  */
    void swap(MaxStack & x ){q.swap(x.q) ;} ;
};