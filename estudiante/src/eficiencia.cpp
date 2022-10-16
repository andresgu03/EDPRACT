#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include "image.h"

/**
         @page page_efficiency Análisis de eficiencia del método ShuffleRows().


         @section sec_Theoric_Analysis Análisis teórico

         Hablaremos de la eficiencia usando la notación O.\n Para la representación inicial, donde byte ** img apunta a una lista de bytes seguidos en memoria, la eficiencia de este método sería de __O(filas*columnas)__ es decir, para un número variable de filas y columnas, sería una eficienca de **n²**. Dejando un número fijo de filas sería lineal (**O(cols)**) respecto al número de columnas y, dejando un número fijo de columnas sería análogo para el número de filas. \n Para una nueva representación donde dejamos de asimilar que todas las filas están consecutivas en memoria y cada puntero de la primera columna apunta a una fila, la eficiencia pasaría a ser **O(filas)** es decir, únicamente dependería linealmente del número de filas, ya que el método sólo tendría que cambiar las filas a las que apunta cada puntero de la primera columna.

         @section sec_Empyric_Analysis Análisis empírico

         Para el análisis empírico haremos unas pruebas de tiempo del método __ShuffleRows__ usando las dos implementaciones y viendo cómo las gráficas del tiempo respecto a un valor variable ( que será o bien número de filas y columnas, únicamente número de filas con columnas fijas o únicamente número de columnas con filas fijas).

       **/

using namespace std;

void chrono_experiment(int image_size, int repetitions) {
    // Inicializamos el experimento antes del bucle de conteo de tiempo para no afectar al análisis
    Image imagen(image_size , image_size, (byte)127) ;

    // Medimos el tiempo antes de iniciar el expermiento
    chrono::high_resolution_clock::time_point start_time = chrono::high_resolution_clock::now();

    // Realizamos el experimento tantas veces como indique repetitions, para tener cierta robustez
    // en el resultado (no todas las ejecuciones tardan lo mismo)
    for (int k = 0; k < repetitions; ++k){
        imagen.ShuffleRows();
    }

    // Medimos el tiempo al finalizar el experimento
    chrono::high_resolution_clock::time_point finish_time = chrono::high_resolution_clock::now();

    // Calculamos la diferencia entre el inicio y el final
    chrono::duration<double> total_duration = chrono::duration_cast<chrono::duration<double>>(finish_time - start_time);

    // Dividimos el tiempo total entre el número de repeticiones para obtener el tiempo medio por ejecución
    cout << image_size << "\t" << total_duration.count()/repetitions << endl;
}
int main() {

    for (int i = 100; i <= 5000; i += 100){
        chrono_experiment(i, 30);
    }
    return 0;
}