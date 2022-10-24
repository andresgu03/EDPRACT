/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author Pablo García Bas
 * @author Andrés Gutiérrez Armenteros
 */

#include <maxqueue.h>
#include <stack>

void MaxQueue::push(int new_value){

    std::stack<element> pila_aux;

    if(this->pila.empty()) { // Si la pila estaba vacia -> value=max=new_value

        element aux;
        aux.value = new_value;
        aux.max = new_value;

        this->pila.push(aux);

    }

    else{ // Si la pila NO estaba vacia

        element new_elem; // Elemento nuevo de la pila principal

        if(new_value > front().max){ // Caso 1 (nuevo maximo = new_value)

            new_elem.value = new_value;
            new_elem.max = new_value;

            while(!this->pila.empty()){ // 1) Mover a pila_aux
                pila_aux.push(this->pila.top());
                this->pila.pop();
            }

            this->pila.push(new_elem); // 2) Mover nuevo elemento a pila ppal.

            while(!pila_aux.empty()){
                element aux = pila_aux.top();
                aux.max = new_value; // 3) Actualizar el maximo de cada elemento de pila_aux

                this->pila.push(aux); // 4) Mover el elemento actualizado a pila ppal.
                pila_aux.pop();
            }

        }

        else{ // Caso 2 (new_value <= front().max) -> (nuevo maximo = anterior maximo)

            int old_max = front().max; // En este caso, el maximo se mantiene

            new_elem.value = new_value;
            new_elem.max = old_max;

            while(!this->pila.empty()){ // 1) Mover a pila_aux
                pila_aux.push(this->pila.top());
                this->pila.pop();
            }

            this->pila.push(new_elem); // 2) Mover nuevo elemento a pila ppal.

            while(!pila_aux.empty()){
                this->pila.push(pila_aux.top()); // 4) Mover el elemento actualizado a pila ppal.
                pila_aux.pop();
            } // Ya no necesario actualizar el maximo de cada elemento (tan solo volcar el contenido de pila_aux)

        }

    }

};

void MaxQueue::pop(){

    std::stack<element> pila_aux;

    int top_value, top_max;

    top_value = this->pila.top().value;
    top_max = this->pila.top().max;

    this->pila.pop();

    if(top_value == top_max && !empty()) { // En este caso, no basta con hacer pila.pop()

        int new_max = front().value;

        pila_aux.push(front());
        this->pila.pop();

        while(!this->pila.empty()){ // 1) Mover pila principal a pila auxiliar + calcular el nuevo maximo

            int next_value = front().value;

            if(next_value > new_max)
                new_max = next_value;

            pila_aux.push(front());
            this->pila.pop();

        }

        while (!pila_aux.empty()){ // 2) Mover de vuelta pila auxiliar a pila principal + cambiando el maximo

            element aux;
            aux.value = pila_aux.top().value;
            aux.max = new_max;

            this->pila.push(aux);
            pila_aux.pop();

        }

    }

};
