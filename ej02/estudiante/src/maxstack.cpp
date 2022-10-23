/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */

#include "maxstack.h"
#include <assert.h>



MaxStack::MaxStack(const MaxStack & otro) {
    assert( this != &otro);
    q = otro.q ;
}

MaxStack & MaxStack::operator=(const MaxStack &otro) {
    assert( this != &otro);
    q = otro.q ;
    return *this ;
}

void MaxStack::push(int val ) {
    element e ;
    e.value = val ;
    if(val > q.front().maximum){
        e.maximum = val ;
    }
    else
        e.maximum = q.front().maximum ;

    q.push(e) ;

    for (int i = 1 ; i < q.size() ; i++ ){
        q.push(q.front());
        q.pop();
    }
}

void MaxStack::pop() {
    q.pop() ;
}

element MaxStack::top(){
    return (q.front()) ;
}

ostream& operator<<(std::ostream &os, const element obj) {
    os << obj.value << "," << obj.maximum ;
    return os ;
}