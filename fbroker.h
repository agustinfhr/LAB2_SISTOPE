
#include "juego.h" // Estructura de datos para los juegos.
#include "year.h" // Estructura de datos para los anios.

/*
Entradas: Un arreglo de juegos de tipo juego.
Salidas: Un entero que representa la cantidad de anios distintos que se encuentran en la informacion recibida.
Descripción: Función que se encarga de calcular la cantidad de anios distintos que se encuentran en el arreglo
            de juegos, este valor obtenido ademas sirve para saber la cantidad de procesos hijos a crear.
*/
int calcularAnios(juego *juegos);


juego * leerArchivoEntrada(char *nombreArchivo);

juego* leerArchivoPorLinea(char *nombreArchivo, int posicion);
