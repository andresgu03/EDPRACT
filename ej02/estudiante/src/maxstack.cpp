/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */

#include "maxstack.h"


void MaxStack::push(int val ) {
    queue<element> cola_els;
    element e;
    e.maximum = val;
    e.value = val;

    if(size() != 0) {
        if (top().maximum >= e.maximum)
            e.maximum = top().maximum;
    }

    cola_els.push(e);

    while(!empty()){
        cola_els.push(top());
        pop();
    }

    while(!cola_els.empty()){
        q.push(cola_els.front());
        cola_els.pop();
    }
}

void MaxStack::pop(){
    if ( !q.empty()){
        q.pop() ;
    }
}

std::ostream & operator<<(std::ostream& os, const element& elem){ // Operador de salida sobrecargado (struct element)

    os << elem.value << "," << elem.maximum;

    return os;

}