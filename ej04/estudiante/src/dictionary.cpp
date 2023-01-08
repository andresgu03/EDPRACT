/**
 * @file dictionary.cpp
 * @brief Implementación del TDA Dictionary
 * @author Andrés Gutiérrez Armenteros
 * @author Pablo García Bas
 * @date Diciembre 2022
 */

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
  node prev_child, curr_child = current.left_child();

  for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
    prev_child = curr_child;
    if ((*curr_child).character == character) {
      return curr_child;
    }
  }
  if (!prev_child.is_null()) {
    return prev_child;
  }
  return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
  node insertion_position = findLowerBoundChildNode(character, current);
  if (insertion_position == current){
    this->words.insert_left_child(current, char_info(character));
    return insertion_position.left_child();
  } else if ((*insertion_position).character != character){
    this->words.insert_right_sibling(insertion_position, char_info(character));
    return insertion_position.right_sibling();
  } else {
    return insertion_position;
  }
}

int Dictionary::getOccurrences(node curr_node, char c){
    int num_ocurr = 0;

    if ((*curr_node).character == tolower(c)) // If current node letter == c --> Increment num_ocurr
        num_ocurr++;

    if (!curr_node.left_child().is_null()) // If left_child is not null -> Call getOcurrences
        num_ocurr += getOccurrences(curr_node.left_child(), c);

    if (!curr_node.right_sibling().is_null()) // If right_sibling is not null -> Call getOcurrences
        num_ocurr += getOccurrences(curr_node.right_sibling(), c);

    return num_ocurr;

}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){

    pair<int, int> num_usages(0,0);           // FIRST: character num_usages below current node
                                                    // SECOND: num_words ending below current node
    pair <int, int> child_usages(0,0);
    pair <int, int> sibling_usages(0,0);

    // (1) Sum of contributions between left_child and right_sibling
    if (!curr_node.left_child().is_null())
        child_usages = getTotalUsages(curr_node.left_child(), c);
    if (!curr_node.right_sibling().is_null())
        sibling_usages = getTotalUsages(curr_node.right_sibling(), c);

    num_usages.first = (child_usages.first + sibling_usages.first);
    num_usages.second = (child_usages.second + sibling_usages.second);

    // (2) Independent checks for current node:

    // (2.1) If current node character matches --> Every word below must share this letter (whole words in left_child)
    if ((*curr_node).character == tolower(c))
        num_usages.first += child_usages.second;

    // (2.2) If current node is the end of a valid word --> Increment number of words
    if((*curr_node).valid_word){
        num_usages.second++;
        if ((*curr_node).character == tolower(c))    // Also, if current node character matches, it means another word
            num_usages.first++;             // uses the letter (not just those that fall below - already in 2.1)
    }

    return num_usages;
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
  this->words.set_root(char_info());
  this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
  this->words = other.words;
  this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
  this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->findLowerBoundChildNode(word[i], current);
    if ((*current).character != word[i]) {
      return false;
    }
  }

  return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
  node current = this->words.get_root();
  for (int i = 0; i < word.size(); ++i){
    current = this->insertCharacter(word[i], current);
  }

  if (!(*current).valid_word) {
    (*current).valid_word = true;
    this->total_words++;
    return true;
  }

  return false;
}

bool Dictionary::erase(const std::string & val){
  node current = this->words.get_root();
  for (int i = 0; i < val.size(); ++i){
    current = this->findLowerBoundChildNode(val[i], current);
    if ((*current).character != val[i]) {
      return false;
    }
  }
  if ((*current).valid_word){
    (*current).valid_word = false;
    this->total_words--;
    return true;
  }
  return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
  if (this != &dic){
    this->words.clear();
    this->words = dic.words;
    this->total_words = dic.total_words;
  }
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
  for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
    os << *it << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream &is, Dictionary &dict){
  std::string curr_word;
  while (getline(is, curr_word)){
    dict.insert(curr_word);
  }
  return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
    return getOccurrences(this->words.get_root(), c);
}

int Dictionary::getTotalUsages(const char c){
    return getTotalUsages(this->words.get_root(), c).first;
}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator() {
    this->iter = tree<char_info>::const_preorder_iterator();
    this->curr_word = "";
}

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator other_iter) {
    this->iter = other_iter ;
}

std::string Dictionary::iterator::operator*() {
    return this->curr_word ;
}

Dictionary::iterator &Dictionary::iterator::operator++() {
    int nivel_actual = this->iter.get_level();
    Dictionary::iterator copy (*this) ;
    if( ++(copy.iter) != Dictionary::iterator().iter ) {
        do {
            ++this->iter ;
            if (this->iter.get_level() > nivel_actual) {
                this->curr_word += (*(this->iter)).character;
            } else if (this->iter.get_level() == nivel_actual) {
                this->curr_word.pop_back();
                this->curr_word += (*(this->iter)).character;
            } else {
                for (int i = 0; i <= (nivel_actual - this->iter.get_level()); i++) {
                    this->curr_word.pop_back();
                }
                this->curr_word += (*(this->iter)).character;
            }
            nivel_actual = this->iter.get_level();
        } while (!this->iter.operator*().valid_word);
    }
    else {
        this->iter = tree<char_info>::const_preorder_iterator () ;
    }
    return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) {
    return ((this->iter == other.iter) /*&& (this->curr_word == other.curr_word)*/) ;
}

bool Dictionary::iterator::operator!=(const iterator &other) {
    return !((this->iter == other.iter) /*&& (this->curr_word == other.curr_word)*/) ;
}

Dictionary::iterator Dictionary::begin() const {
    Dictionary::iterator iter (words.cbegin_preorder()) ;
    ++iter ;
    return iter ;
}

Dictionary::iterator Dictionary::end() const {
    return words.cend_preorder() ;
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////


Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {

    Dictionary::possible_words_iterator iter (this->words.get_root(),available_characters) ;
    ++iter ;
    return iter ;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
    Dictionary::possible_words_iterator iter ;
    return iter ;
}

Dictionary::possible_words_iterator::possible_words_iterator() {
    multiset<char> empty_bag ;
    this->available_letters = empty_bag ;
    this->level = 0 ;
    this->current_word = "" ;
    this->current_node = node() ;
}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters){
    this->current_node = current_node ;
    multiset<char> bolsa (available_letters.begin(),available_letters.end()) ;
    this->available_letters = bolsa ;
    this->current_word = "" ;
    this->level = 0 ;

}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){
    this->level = other.level ;
    this->current_node = other.current_node ;
    this->current_word = other.current_word ;
    this->available_letters = other.available_letters ;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {
    if (this != &other){
        this->available_letters.clear() ;
        this->available_letters = other.available_letters;
        this->current_word = other.current_word;
        this->current_node = other.current_node ;
        this->level = other.level ;
    }
    return *this;
}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {
    return (this->is_equal(other)) ;
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    return !(this->is_equal(other)) ;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {
    bool is_valid = false ;
    find_left_child(is_valid);
    if(!is_valid){
        *this = possible_words_iterator() ;
    }
    return *this;
}

std::string Dictionary::possible_words_iterator::operator*() const {
    return current_word ;
}

//PRIVATE
bool Dictionary::possible_words_iterator::is_equal(const Dictionary::possible_words_iterator &other) const{
    return ( this->level == other.level && this->current_node == other.current_node && this->current_word == other.current_word) ;
}

void Dictionary::possible_words_iterator::find_left_child(bool & is_valid){
    if(!current_node.left_child().is_null() && !is_valid) {
        current_node = current_node.left_child();
        level++ ;
        char c = current_node.operator*().character ;
        if((this->available_letters.count(c) != 0)){
            current_word += c ;
            this->available_letters.erase(this->available_letters.find(c));

            is_valid = current_node.operator*().valid_word ;
            if(!is_valid){
                find_left_child(is_valid);
                recursive_call(is_valid);
            }
        }
        else{
            recursive_call(is_valid);
        }
    }
    else{
        recursive_call(is_valid);
    }
}
void Dictionary::possible_words_iterator::find_right_sibling(bool & is_valid) {
    if(!current_node.right_sibling().is_null() && !is_valid) {
        current_node = current_node.right_sibling();

        if(level <= current_word.size()){
            available_letters.insert(current_word.back());
            current_word.pop_back() ;
        }
        char c = current_node.operator*().character ;
        if((this->available_letters.count(c) != 0)){
            current_word += c ;
            this->available_letters.erase(this->available_letters.find(c));

            is_valid = is_valid = current_node.operator*().valid_word ;

            if(!is_valid){
                find_left_child(is_valid);
                recursive_call(is_valid);
            }
        }
        else{
            recursive_call(is_valid);
        }
    }
}

void Dictionary::possible_words_iterator::find_right_uncle(bool & is_valid) {
    if(!current_node.parent().is_null() && !is_valid) {
        if(!current_node.parent().right_sibling().is_null()) {
            level--;
            while (level <= current_word.size()) {
                available_letters.insert(current_word.back());
                current_word.pop_back();
            }

            current_node = current_node.parent().right_sibling();

            char c = current_node.operator*().character;

            if ((this->available_letters.count(c) != 0)) {
                current_word += c;
                this->available_letters.erase(this->available_letters.find(c));

                is_valid = current_node.operator*().valid_word ;

                if (!is_valid) {
                    find_left_child(is_valid);
                    recursive_call(is_valid);
                }
            } else {
                recursive_call(is_valid);
            }
        }
        else{
            while (level <= current_word.size()) {
                available_letters.insert(current_word.back());
                current_word.pop_back();
            }
            level-- ;
            current_node = current_node.parent();

            if(!current_node.parent().is_null())
                find_right_uncle(is_valid) ;
        }
    }
}

void Dictionary::possible_words_iterator::recursive_call(bool & is_valid){
    find_right_sibling(is_valid);
    find_right_uncle(is_valid) ;
}
