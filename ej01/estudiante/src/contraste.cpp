/**
 * @file contraste.cpp
 * @brief Fichero que permite ejecutar el método AdjustContrast sobre una imagen, es decir, ajustar su contraste partiendo de unos valores umbrales de entrada y salida.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    int e1, e2, s1, s2 ;
    Image image, result , zoomed;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: subimagen <fichero_origen> <fichero_resultado> <fila> <columna> <filas_subimagen> <columnas_subimagen>\n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    e1 = atoi(argv[3]) ;
    e2 = atoi(argv[4]) ;
    s1 = atoi(argv[5]) ;
    s2 = atoi(argv[6]) ;

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "E1: " << e1 << endl ;
    cout << "E2: " << e2 << endl ;
    cout << "S1: " << s1 << endl ;
    cout << "S2: " << s2 << endl ;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // Calcular la subimagen.
    image.AdjustContrast(e1, e2, s1, s2) ;

    // Guardar la imagen resultado en el fichero
    if (image.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}