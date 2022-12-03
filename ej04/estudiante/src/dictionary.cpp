//
// Created by fluque1995 on 8/9/21.
//

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

/*int Dictionary::getOccurrences(node curr_node, char c){

}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){

}*/

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

/*int Dictionary::getOccurrences(const char c){

}

int Dictionary::getTotalUsages(const char c){

}*/

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
    int nivel_actual = this->iter.get_level() ;
    do {
        ++this->iter;
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
        nivel_actual = this->iter.get_level() ;
    }while(!this->iter.operator*().valid_word) ;
    return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) {
    return ((this->iter == other.iter) && (this->curr_word == other.curr_word)) ;
}

bool Dictionary::iterator::operator!=(const iterator &other) {
    return !((this->iter == other.iter) && (this->curr_word == other.curr_word)) ;
}

Dictionary::iterator Dictionary::begin() const {
    return words.cbegin_preorder() ;
}

Dictionary::iterator Dictionary::end() const {
    return words.cend_preorder() ;
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////


Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {

    Dictionary::possible_words_iterator iter (this->words.get_root(),available_characters) ;
    return iter ;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
    vector<char> empty_bag ;
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
    return (this->available_letters == other.available_letters && this->level == other.level && this->current_node == other.current_node && this->current_word == other.current_word) ;
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    return !(this->available_letters == other.available_letters && this->level == other.level && this->current_node == other.current_node && this->current_word == other.current_word) ;
}

Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++() {
    tree<char_info>::const_preorder_iterator iter (this->current_node) ;
    tree<char_info>::const_preorder_iterator null_iterator ;
    tree<char_info>::const_preorder_iterator aux_iterator ;
    char c ;
    int nivel_actual ;
    do {
        this->level = iter.get_level() ;
        nivel_actual = this->level ;
        ++iter;
        c = (*iter).character ;
        if(this->available_letters.count(c) != 0) {
            if (this->level < nivel_actual) {
                for(int i = 0 ; i < nivel_actual - this->level ; i++){
                    this->available_letters.insert(this->current_word.at(this->current_word.length()-1));
                    this->current_word.pop_back() ;
                }
            }
            else if(this->level == nivel_actual){
                this->available_letters.insert(this->current_word.at(this->current_word.length()-1));
                this->current_word.pop_back() ;
            }
            this->available_letters.erase(this->available_letters.find(c));
            this->current_word += c;
        }
        else{
            ++iter ;
            this->level = iter.get_level() ;
            nivel_actual = this->level ;
        }
    }while(!this->current_node.operator*().valid_word) ;
    return *this;
}

std::string Dictionary::possible_words_iterator::operator*() const {
    return current_word ;
}
