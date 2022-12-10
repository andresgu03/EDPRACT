//
// Created by fluque1995 on 8/9/21.
//

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class Dictionary {
private:
    /**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character it that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */
    struct char_info {
        char character;
        bool valid_word;

        /**
         * Default constructor
         */
        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */
        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        /**
         * @brief Operador de igualdad
         *
         * @param rhs char_info a comparar.
         * @return booleano (true si son iguales o false si son distintos).
         */
        inline bool operator==(const char_info &rhs) {
          return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        /**
         * @brief Operador de desigualdad
         *
         * @param rhs char_info a comparar.
         * @return booleano (true si son distintos o false si son iguales).
         */
        inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }

        inline bool operator*() { return this->character; }

        /**
         * @brief Operador de salida.
         *
         * @param os Flujo de salida.
         * @param other char_info a comparar.
         * @return referencia al flujo de salida.
         */
        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
          os << other.character << (other.valid_word ? "✓" : "×");
          return os;
        }
    };

    tree<char_info> words;
    int total_words;
    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    /**
     * @brief Cuenta las ocurrencias de la letra c en el subárbol que cuelga del node curr_node
     *
     * @param curr_node Nodo del árbol a partir del cual hacer el conteo.
     * @param c Letra a buscar.
     * @return El número de ocurrencias de la letra en el subárbol que cuelga del nodo curr_node.
     */
    int getOccurrences(node curr_node, char c);

    /**
     * @brief Cuenta el número de usos de la letra c para formar palabras en el subárbol que cuelga del node curr_node
     *
     * @param curr_node Nodo del árbol a partir del cual hacer el conteo.
     * @param c Letra a buscar.
     * @return Par<int, int>, el número de usos de letra en el subárbol que cuelga del nodo curr_node, y el número de
     * palabras que terminan por debajo del nodo curr_node.
     */
    std::pair<int, int> getTotalUsages(node curr_node, char c);

public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */
    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */
    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */
    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    /**
     * @brief Cuenta las ocurrencias de la letra c en el diccionario.
     *
     * @param c Letra a buscar.
     * @return El número de ocurrencias de la letra en el diccionario.
     */
    int getOccurrences(const char c);

    /**
     * @brief Cuenta los usos de la letra c para formar palabras en el diccionario.
     *
     * @param c Letra a buscar.
     * @return El número de usos de la letra para formar palabras en el diccionario.
     */
    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    /**
     * @brief TDA iterator de la clase Dictionary
     *
     *
     * Permite recorrer una instancia de la clase Dictionary.
     * Está formado por un iterador de preorden constante de la clase árbol de char_info y por un string que contiene la palabra actual.
    */
    class iterator {
    private:
        std::string curr_word;
        tree<char_info>::const_preorder_iterator iter;

    public:

        /**
         * @brief Constructor sin parámetros. Crea un iterador nulo.
         */
        iterator();

        /**
         * @brief Constructor de copia
         *
         * @param other_iter iterador a copiar.
         */
        iterator(tree<char_info>::const_preorder_iterator other_iter);

        /**
         * @brief Operador *
         *
         * @return string correspondiente a la palabra actual apuntada por el iterador.
         */
        std::string operator*();

        /**
         * @brief Operador de incremento.
         *
         * @return Referencia al iterador que apunta a la posición obtenida tras el incremento.
         */
        iterator &operator++();

        /**
         * @brief Operador de igualdad
         *
         * @param other iterador a comparar.
         * @return booleano (true si son iguales o false si son distintos).
         */
        bool operator==(const iterator &other);

        /**
         * @brief Operador de desigualdad
         *
         * @param other iterador a comparar.
         * @return booleano (true si son distintos o false si son iguales).
         */
        bool operator!=(const iterator &other);

    };

    /**
     * @brief Función begin()
     *
     * @return Iterador que apunta al comienzo de la estructura.
     */
    iterator begin() const;

    /**
     * @brief Función end()
     *
     * @return Iterador que apunta al final de la estructura.
     */
    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    /**
     * @brief TDA iterator de la clase Dictionary de palabras posibles.
     *
     *
     * Permite recorrer una instancia de la clase Dictionary dada una bolsa de letras para que resulte más eficiente.
     * Está formado por la bolsa de letras, representada por un multiconjunto; un string que contiene la palabra actual; un entero, que representa el nivel en el árbol; y un nodo que nos representa la posición exacta en la que nos encontramos dentro del árbol.
    */
    class possible_words_iterator {
    public:
        /**
         * @brief Constructor sin parámetros. Crea un iterador nulo.
         */
        possible_words_iterator();

        /**
         * @brief Constructor con parámetros.
         *
         * @param available_letters Vector que contiene los caracteres disponibles para formar la palabra.
         * @param current_node nodo actual en el que comienza la estructura.
         */
        possible_words_iterator(node current_node, vector<char> available_letters);

        /**
         * @brief Constructor de copia.
         *
         * @param other Iterador a copiar.
         */
        possible_words_iterator(const possible_words_iterator &other);

        /**
         * @brief Operador de asignación.
         *
         * @param other Iterador que se desea copiar.
         * @return Referencia al iterador.
         */
        possible_words_iterator &operator=(const possible_words_iterator &other);

        /**
         * @brief Operador de igualdad
         *
         * @param other iterador a comparar.
         * @return booleano (true si son iguales o false si son distintos).
         */
        bool operator==(const possible_words_iterator &other) const;

        /**
         * @brief Operador de desigualdad
         *
         * @param other iterador a comparar.
         * @return booleano (true si son distintos o false si son iguales).
         */
        bool operator!=(const possible_words_iterator &other) const;

        /**
         * @brief Operador de incremento.
         *
         * @return Referencia al iterador tras el incremento.
         */
        possible_words_iterator &operator++();

        /**
         * @brief Operador *
         *
         * @return string correspondiente a la palabra actual apuntada por el iterador.
         */
        std::string operator*() const;

    private:
        multiset<char> available_letters;
        int level;
        node current_node;
        string current_word;

    };

    /**
     * @brief Función possible_words_begin()
     *
     * @param available_characters vector que contiene todos los caracteres disponibles.
     * @return Iterador que apunta al comienzo de la estructura.
     */
    possible_words_iterator possible_words_begin(vector<char> available_characters) const;

    /**
     * @brief Función possible_words_end()
     *
     * @return Iterador que apunta al final de la estructura.
     */
    possible_words_iterator possible_words_end() const;
};

#endif //TREE_DICTIONARY_HPP
