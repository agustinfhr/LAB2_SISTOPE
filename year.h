#ifndef year_h_
#define year_h_

// Estructura de datos utilizada para la interpretacion y procesado de los datos que se pide
// que hagan los procesos hijos.
typedef struct year_struct {
    int  numAnio;   // Cantidad de anios distintos en el archivo.
    float  juegoMasCaro;    // Juego mas caro del anio analizado.
    char *nombreMasCaro;
    float  juegoMasBarato;  // Juego mas barato del anio analizado.
    char *nombreMasBarato;
    float  promPrecios; // Promedio de los precios del anio analizado.
    float windows;
    float mac;
    float lynux;
    int numJuegosPorAnio;
    int cantJuegosGratis; // Cantidad de juegos gratis.
    char *juegosGratis; // Arreglo para guardar los juegos gratis.
    
    int pid_padre;  // Process ID del proceso padre.

    int lineaInicial;   // Valor para saber en que linea del archivo se encuentra el analisis.
    int lineaFinal; // Valor para saber en que linea del archivo se encuentra el analisis.

    char* nombreJuego;
    float precio;
    char* gratis;
    char* windowsIn;
    char* macIn;
    char* lynuxIn;

} year;

#endif
