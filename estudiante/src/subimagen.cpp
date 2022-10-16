/**
 * @file subimagen.cpp
 * @brief Fichero que permite ejecutar el método Crop sobre una imagen, es decir, generar una subimagen.
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    int fila, col, nfils, ncols ;
    Image image, result ;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: subimagen <fichero_origen> <fichero_resultado> <fila> <columna> <filas_subimagen> <columnas_subimagen>\n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    fila = atoi(argv[3]) ;
    col = atoi(argv[4]) ;
    nfils = atoi(argv[5]) ;
    ncols = atoi(argv[6]) ;

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Fila: " << fila << endl ;
    cout << "Columna: " << col << endl ;
    cout << "Filas subimagen: " << nfils << endl ;
    cout << "Columnas subimagen: " << ncols << endl ;

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
    result = image.Crop(fila, col, nfils, ncols) ;

    // Guardar la imagen resultado en el fichero
    if (result.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}

