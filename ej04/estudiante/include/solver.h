/**
 * @file solver.h
 * @brief Archivo de especificación del TDA Solver
 * @author Pablo García Bas
 * @author Andrés Gutiérrez Armenteros
 * @date Diciembre 2022
 */

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H

#include "vector"
#include "dictionary.h"
#include "letters_set.h"
#include "algorithm"

/**
     * @brief TDA Solver
     *
     *
     * Permite obtener la mejor/mejores soluciones (no necesariamente solución única) para una partida y modo de juego determinado.
     * Está formado por un objeto del TDA Dictionary (posibles soluciones), así como uno del TDA LettersSet (letras disponibles en la partida)
    */
class Solver{

private:
    Dictionary dictionary;
    LettersSet letters;

    /**
     * @brief Construye el vector de soluciones (por puntuación) a partir de las letras de una partida.
     * @param available_letters Vector de letras disponibles para la partida.
     * @return Par <vector<string>, int>, con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen.
     */
    pair<vector<string>,int> getSolutionsByScore(const vector<char>& available_letters);

    /**
     * @brief Construye el vector de soluciones (por longitud) a partir de las letras de una partida.
     * @param available_letters Vector de letras disponibles para la partida.
     * @return Par <vector<string>, int>, con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen.
     */
    pair<vector<string>,int> getSolutionsByLength(const vector<char>& available_letters);

    /**
     * @brief Construye el vector de soluciones (por puntuación) a partir de las letras de una partida.
     * @param available_letters Vector de letras disponibles para la partida.
     * @return Par <vector<string>, int>, con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen.
     */

    /**
     * @brief Comprueba si una palabra se puede formar con un vector de letras disponibles
     * @param word Palabra a comprobar.
     * @param letters Vector de letras disponibles
     * @return Bool indicando si la palabra se puede formar. True indica que se puede, false indica lo contrario.
     */
    bool is_word_possible(string word, vector<char> letters);

public:

    /**
     * @brief Constructor con parámetros. Crea un Solver que tiene asociado un Dictionary y un LettersSet.
    */
    Solver(const Dictionary& dict, const LettersSet& letters_set);

    /**
     * @brief Construye el vector de soluciones a partir de las letras de una partida.
     * Dado un conjunto de letras posibles para crear una solución, y el modo de juego con el que se juega la partida,
     * se construye un vector con las mejores soluciones encontradas en función del tipo de juego planteado.
     * @param available_letters Vector de letras disponibles para la partida.
     * @param score_game Bool indicando el tipo de partida. True indica que la partida se juega a puntuación, false que
     * se juega a longitud.
     * @return Par <vector<string>, int>, con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen.
     */
    pair<vector<string>,int> getSolutions(const vector<char>& available_letters, bool score_game);

};

// SOLVER EFICIENTE

/**
     * @brief TDA SolverEficiente
     *
     *
     * Permite obtener la mejor/mejores soluciones (no necesariamente solución única) para una partida y modo de juego determinado.
     * Está formado por un objeto del TDA Dictionary (posibles soluciones), así como uno del TDA LettersSet (letras disponibles en la partida)
     * Se supone una versión más eficiente del TDA Solver, en tanto que itera por el diccionario descartando ramas donde no se puede formar palabra con las letras disponibles.
    */
class SolverEficiente{

private:
    Dictionary dictionary;
    LettersSet letters;

    /**
     * @brief Construye el vector de soluciones (por puntuación) a partir de las letras de una partida.
     * @param available_letters Vector de letras disponibles para la partida.
     * @return Par <vector<string>, int>, con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen.
     */
    pair<vector<string>,int> getSolutionsByScore(const vector<char>& available_letters);

    /**
     * @brief Construye el vector de soluciones (por longitud) a partir de las letras de una partida.
     * @param available_letters Vector de letras disponibles para la partida.
     * @return Par <vector<string>, int>, con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen.
     */
    pair<vector<string>,int> getSolutionsByLength(const vector<char>& available_letters);

public:

    /**
     * @brief Constructor con parámetros. Crea un SolverEficiente que tiene asociado un Dictionary y un LettersSet.
    */
    SolverEficiente(const Dictionary& dict, const LettersSet& letters_set);

    /**
     * @brief Construye el vector de soluciones a partir de las letras de una partida.
     * Dado un conjunto de letras posibles para crear una solución, y el modo de juego con el que se juega la partida,
     * se construye un vector con las mejores soluciones encontradas en función del tipo de juego planteado.
     * @param available_letters Vector de letras disponibles para la partida.
     * @param score_game Bool indicando el tipo de partida. True indica que la partida se juega a puntuación, false que
     * se juega a longitud.
     * @return Par <vector<string>, int>, con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen.
     */
    pair<vector<string>,int> getSolutions(const vector<char>& available_letters, bool score_game);

};

#endif //P04_JUEGO_LETRAS_SOLVER_H
