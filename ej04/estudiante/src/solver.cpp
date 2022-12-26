/**
 * @file solver.h
 * @brief Implementación del TDA Solver
 * @author Pablo García Bas
 * @author Andrés Gutiérrez Armenteros
 * @date Diciembre 2022
 */

#include "solver.h"
#include "string"
#include "vector"

//******************************************

// SOLVER (NO EFICIENTE)

//******************************************

// PUBLIC //
Solver::Solver(const Dictionary& dict, const LettersSet& letters_set){  // Using copy constructors from Dictionary and
    this->dictionary = dict;                                            // LettersSet
    this->letters = letters_set;
}

pair<vector<string>,int> Solver::getSolutions(const vector<char>& available_letters, bool score_game){
    pair<vector<string>,int> solutions_pair;
    if(score_game)          // By Score
        solutions_pair = getSolutionsByScore(available_letters);
    else                    // By Length
        solutions_pair = getSolutionsByLength(available_letters);
    return solutions_pair;
}

// PRIVATE //
bool Solver::is_word_possible(string word, vector<char> letters){

    vector<char> letters_copy(letters); // Copy necessary, as "available_letters" is a constant reference

    bool is_possible = true;
    int i=0;

    if(word.size() > letters_copy.size()) // 1) First check
        is_possible = false;

    while(is_possible && i<word.size()) { // 2) Second check
        vector<char>::iterator it = find(letters_copy.begin(), letters_copy.end(), word.at(i));
        if (it != letters_copy.end()) // 2.1) Word's letter i was found in "letters" vector
            letters_copy.erase(it);
        else { // Still, word's letter i could be lowercase and "letters" vector's letters uppercase, and therefore not match
            it = find(letters_copy.begin(), letters_copy.end(), toupper(word.at(i)));
            if (it != letters_copy.end())
                letters_copy.erase(it);
            else // 2.2) Letter was not found
                is_possible = false;
        }
        i++;
    }
    return is_possible;
}

pair<vector<string>,int> Solver::getSolutionsByScore(const vector<char>& available_letters){
    int score;
    pair<vector<string>,int> solutions_pair;

    for(Dictionary::iterator it=this->dictionary.begin(); it!=this->dictionary.end(); ++it){

        score = this->letters.getScore(*it); // O(n)

        if (score >= solutions_pair.second){ // Only if word's score is at least as good as the best previous
                                             // should it be studied if is possible as word
            if(is_word_possible(*it, available_letters)){ // O(n^2)

                if(score == solutions_pair.second)
                    solutions_pair.first.push_back(*it);

                else if(score > solutions_pair.second){
                    solutions_pair.first.clear();
                    solutions_pair.first.push_back(*it);
                    solutions_pair.second = score;
                }
            }
        }
    }
    return solutions_pair;
}

pair<vector<string>,int> Solver::getSolutionsByLength(const vector<char>& available_letters){
    int length;
    pair<vector<string>,int> solutions_pair;

    for(Dictionary::iterator it=this->dictionary.begin(); it!=this->dictionary.end(); ++it){

        length = (*it).size(); // O(n)

        if (length >= solutions_pair.second){   // Only if word's length is at least as good as the best previous
                                                // should it be studied if is possible as word
            if(is_word_possible(*it, available_letters)){ // O(n^2)

                if(length == solutions_pair.second)
                    solutions_pair.first.push_back(*it);

                else if(length > solutions_pair.second){
                    solutions_pair.first.clear();
                    solutions_pair.first.push_back(*it);
                    solutions_pair.second = length;
                }
            }
        }
    }
    return solutions_pair;
}

//******************************************

// SOLVER (EFICIENTE)

//******************************************

// PUBLIC //
SolverEficiente::SolverEficiente(const Dictionary &dict, const LettersSet &letters_set){  // Using copy constructors
    this->dictionary = dict;                                                              // from Dictionary and
    this->letters = letters_set;                                                          // LettersSet
}

pair<vector<string>,int> SolverEficiente::getSolutions(const vector<char>& available_letters, bool score_game){
    pair<vector<string>,int> solutions_pair;
    if(score_game)          // By Score
        solutions_pair = getSolutionsByScore(available_letters);
    else                    // By Length
        solutions_pair = getSolutionsByLength(available_letters);
    return solutions_pair;
}

// PRIVATE //
pair<vector<string>,int> SolverEficiente::getSolutionsByScore(const vector<char>& available_letters){
    int score;
    pair<vector<string>,int> solutions_pair;

    for(Dictionary::possible_words_iterator it=dictionary.possible_words_begin(available_letters); it!=dictionary.possible_words_end(); ++it){

        score = this->letters.getScore(*it); // O(n)

        if(score == solutions_pair.second)
            solutions_pair.first.push_back(*it);

        else if(score > solutions_pair.second){
            solutions_pair.first.clear();
            solutions_pair.first.push_back(*it);
            solutions_pair.second = score;
        }
    }
    return solutions_pair;
}

pair<vector<string>,int> SolverEficiente::getSolutionsByLength(const vector<char>& available_letters){
    int length;
    pair<vector<string>,int> solutions_pair;

    for(Dictionary::possible_words_iterator it=dictionary.possible_words_begin(available_letters); it!=dictionary.possible_words_end(); ++it){

        length = (*it).size(); // O(n)

        if(length == solutions_pair.second)
            solutions_pair.first.push_back(*it);

        else if(length > solutions_pair.second){
            solutions_pair.first.clear();
            solutions_pair.first.push_back(*it);
            solutions_pair.second = length;
        }
    }
    return solutions_pair;
}
