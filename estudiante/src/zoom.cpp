// Fichero: zoom.cpp
// Hace zoom en una imagen PGM
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    int fila, col, lado ;
    Image image, result , zoomed;

    // Comprobar validez de la llamada
    if (argc != 6){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: subimagen <fichero_origen> <fichero_resultado> <fila> <columna> <filas_subimagen> <columnas_subimagen>\n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    fila = atoi(argv[3]) ;
    col = atoi(argv[4]) ;
    lado = atoi(argv[5]) ;

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Fila: " << fila << endl ;
    cout << "Columna: " << col << endl ;
    cout << "Lado del cuadrado: " << lado << endl ;

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
    result = image.Crop(fila, col, lado, lado) ;

    // Calcular el zoom.
    zoomed = result.Zoom2X() ;

    // Guardar la imagen resultado en el fichero
    if (zoomed.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}


