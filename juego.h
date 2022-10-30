#ifndef juego_h_
#define juego_h_

// Estructura de datos utilizada para la interpretacion de los datos leidos en el archivo
// de entrada (juegos con su respectiva informacion).
typedef struct juego_struct {
    int id;
    char *nombre;
    int restriccionEdad;    // 0 o 18 dependiendo si posee o no restriccion de edad.
    float precio;   // Al estar en dolares, el precio del juego se recibe como flotante.
    char prox[6];   // Si va a salir proximamente el juego.
    int fecha;  // Anio de lanzamiento del juego.
    char gratis[10]; // True o False dependiendo si el juego es gratis.
    char windows[10];   // Yes o no dependiendo si el juego se encuentra disponible para windows.
    char mac[10];   // Yes o no dependiendo si el juego se encuentra disponible para mac.
    char lynux[4];  // Yes o no dependiendo si el juego se encuentra disponible para linux.
    int largoNombre;    // Se almacena el largo del nombre del juego que se encuentra en char* nombre.
    int nJuegos;    // Numero total de juegos.
    int inicio;
    int final;
    int posicion;

} juego;

#endif