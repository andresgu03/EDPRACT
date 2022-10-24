#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "maxqueue.h"

using namespace std;

std::ostream& operator<<(std::ostream& flujo, const element& elem){ // Operador de salida sobrecargado (struct element)

    flujo << elem.value;
    flujo << ",";
    flujo << elem.max;

    return flujo;

};

int main(int argc, char *argv[]){

     // Run the current exercise
     MaxQueue queue;

     for(int i = 1; i < argc; i++){
         if (argv[i][0] == '.'){
             cout << queue.front() << endl;
             queue.pop();
         } else {
             queue.push(atoi(argv[i]));
         }
     }
     return 0;
}
